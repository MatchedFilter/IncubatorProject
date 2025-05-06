#include "Incubator/Presenter/Presenter.h"
#include "Incubator/IncubatorData/IncubatorInformationData.h"
#include "Incubator/IncubatorDependencies.h"
#include "Incubator/Time/TimeUtils.h"

namespace Incubator
{

    bool Presenter::ReadModel(IModel *model, PidData &pid, SettingsData &settings, TimeInformationData &timeInformation)
    {
        bool bResult = false;
        if (model != nullptr)
        {
            constexpr uint32_t MAX_TRY_COUNT = static_cast<uint32_t>(5UL);
            bool bTimeRead = false;
            bool bSettingsRead = false;
            bool bPidRead = false;
            for (uint32_t i = static_cast<uint32_t>(0UL); i < MAX_TRY_COUNT; i++)
            {
                if (false == bTimeRead)
                {
                    bTimeRead = model->Get(timeInformation);
                }
                if (false == bSettingsRead)
                {
                    bSettingsRead = model->Get(settings);
                }
                if (false == bPidRead)
                {
                    bPidRead = model->Get(pid);
                }
                if (bTimeRead && bSettingsRead && bPidRead)
                {
                    bResult = true;
                    break;
                }
            }
        }
        return bResult;
    }
    
    bool Presenter::UpdateModel(IModel *model, PidData& data)
    {
        bool bResult = false;
        constexpr uint32_t MAX_TRY_COUNT = static_cast<uint32_t>(5UL);
        if (model != nullptr)
        {
            for (uint32_t i = static_cast<uint32_t>(0UL); i < MAX_TRY_COUNT; i++)
            {
                if (model->Update(data))
                {
                    bResult = true;
                    break;
                }
            }
        }
        return bResult;
    }
    
    bool Presenter::UpdateModel(IModel *model, SettingsData& data)
    {
        bool bResult = false;
        constexpr uint32_t MAX_TRY_COUNT = static_cast<uint32_t>(5UL);
        if (model != nullptr)
        {
            for (uint32_t i = static_cast<uint32_t>(0UL); i < MAX_TRY_COUNT; i++)
            {
                if (model->Update(data))
                {
                    bResult = true;
                    break;
                }
            }
        }
        return bResult;
    }
    
    bool Presenter::UpdateModel(IModel *model, TimeInformationData& data)
    {
        bool bResult = false;
        constexpr uint32_t MAX_TRY_COUNT = static_cast<uint32_t>(5UL);
        if (model != nullptr)
        {
            for (uint32_t i = static_cast<uint32_t>(0UL); i < MAX_TRY_COUNT; i++)
            {
                if (model->Update(data))
                {
                    bResult = true;
                    break;
                }
            }
        }
        return bResult;
    }

    bool Presenter::SyncModels(PidData &pid, SettingsData &settings, TimeInformationData &timeInformation)
    {
        PidData pid1;
        SettingsData settings1;
        TimeInformationData timeInformation1;
        timeInformation1.Reset();
        const bool bModelValid = ReadModel(m_Model, pid1, settings1, timeInformation1);

        PidData pid2;
        SettingsData settings2;
        TimeInformationData timeInformation2;
        timeInformation2.Reset();
        const bool bSpareModelValid = ReadModel(m_SpareModel, pid1, settings1, timeInformation1);

        bool bResult = true;
        if (bModelValid && bSpareModelValid)
        {
            if(timeInformation1.m_CurrentTimestampInSecond < timeInformation2.m_CurrentTimestampInSecond)
            {
                pid.Copy(pid2);
                settings.Copy(settings2);
                timeInformation.Copy(timeInformation2);

            }
            else
            {
                pid.Copy(pid1);
                settings.Copy(settings1);
                timeInformation.Copy(timeInformation1);

            }
        }
        else if (bModelValid)
        {
            pid.Copy(pid1);
            settings.Copy(settings1);
            timeInformation.Copy(timeInformation1);
        }
        else if (bSpareModelValid)
        {
            pid.Copy(pid2);
            settings.Copy(settings2);
            timeInformation.Copy(timeInformation2);
        }
        else
        {
            bResult = false;
        }
        if (bResult)
        {
            (void) UpdateModel(m_Model, pid);
            (void) UpdateModel(m_Model, settings);
            (void) UpdateModel(m_Model, timeInformation);
            (void) UpdateModel(m_SpareModel, pid);
            (void) UpdateModel(m_SpareModel, settings);
            (void) UpdateModel(m_SpareModel, timeInformation);
        }
        return bResult;
    }
    

    Presenter::Presenter() :
        m_View { nullptr },
        m_Model { nullptr },
        m_bIsInitialized { false }
    {
    }

    Presenter::~Presenter()
    {
    }

    void Presenter::Initialize(IView *view, IModel *model, IModel* spareModel)
    {
        m_View = view;
        m_Model = model;
        m_SpareModel = spareModel;

        m_PidDataChangedEventHandler.Initialize(m_Model, m_SpareModel);
        m_SettingsDataCache.Initialize(m_Model, m_SpareModel, m_View);
        m_TimeInformationDataChangedEventHandler.Initialize(m_Model, m_SpareModel);

        DataChangedEventHandlers eventHandlers;
        eventHandlers.Reset();
        eventHandlers.m_PidDataChangedEventHandler = &m_PidDataChangedEventHandler;
        eventHandlers.m_SettingsDataChangedEventHandler = &m_SettingsDataCache;
        eventHandlers.m_TimeInformationDataChangedEventHandler = &m_TimeInformationDataChangedEventHandler;
        
        if (m_View->Initialize(&eventHandlers))
        {
            PidData pid;
            SettingsData settings;
            TimeInformationData timeInformation;
            pid.Reset();
            settings.Reset();
            timeInformation.Reset();
            // (void) UpdateModel(m_Model, pid);
            // (void) UpdateModel(m_Model, settings);
            // (void) UpdateModel(m_Model, timeInformation);
            // (void) UpdateModel(m_SpareModel, pid);
            // (void) UpdateModel(m_SpareModel, settings);
            // (void) UpdateModel(m_SpareModel, timeInformation);
            
            if (SyncModels(pid, settings, timeInformation))
            {
                m_bIsInitialized = true;
                m_View->UpdateSettingsData(settings);
                m_View->UpdateTimeInformationData(timeInformation);
            }
            else
            {
                m_View->OnModelFailure();
            }
        }

    }

    void Presenter::UpdateTemperature(const double &temperatureInCelcius)
    {
        m_View->UpdateTemperature(temperatureInCelcius);
    }

    void Presenter::UpdateHumidity(const uint8_t humidityInPercent)
    {
        m_View->UpdateHumidity(humidityInPercent);
    }

    void Presenter::OnTemperatureFailure()
    {
        m_View->OnTemperatureFailure();
    }

    void Presenter::OnHumidityFailure()
    {
        m_View->OnHumidityFailure();
    }


    void Presenter::Run(void)
    {
    }

} // namespace Incubator
