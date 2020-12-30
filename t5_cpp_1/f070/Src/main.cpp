/**
  ******************************************************************************
  * @file    UART/UART_TwoBoards_ComIT/Src/main.c 
  * @author  MCD Application Team
  * @brief   This sample code shows how to use UART HAL API to transmit
  *          and receive a data buffer with a communication process based on
  *          IT transfer. 
  *          The communication is done using 2 Boards.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <iostream>
#include <variant>
#include <algorithm>
#include <vector>


UART_HandleTypeDef UartHandle;


class EmptyDevice
{
public:
    void print_me()const
    {
        std::cout<<"EmptyDevice"<<'\n';
    }
};

class Pin
{
public:
    void print_me()const
    {
        std::cout<<"Pin"<<'\n';
    }
};

class UART
{
public:
    void print_me()const
    {
        std::cout<<"UART"<<'\n';
    }
};

class SoftUART
{
public:
    void print_me()const
    {
        std::cout<<"SoftUART"<<'\n';
    }
};


//// T1
//_LIBCPP_BEGIN_NAMESPACE_STD
//// T2
//using namespace std;

using ControlWay=std::variant<EmptyDevice,Pin,UART,SoftUART>;


class DeviceList
{
    std::vector<ControlWay*> m_list;
public:
    bool addDevice(ControlWay* device)
    {
        m_list.push_back(device);
        return true;
    }
    
    bool removeDevice(ControlWay* device)
    {
        m_list.erase(std::remove(m_list.begin(),m_list.end(),device),m_list.end());
        return true;
    }
    
    void print_me()const
    {
        for(auto* d:m_list)
        {
            std::visit([](auto& device)
            {
                device.print_me();
            },*d);
        }
    }
};

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  DeviceList m_DeviceList;
    
    m_DeviceList.addDevice(new ControlWay{Pin{}});
    m_DeviceList.addDevice(new ControlWay{UART{}});
    m_DeviceList.addDevice(new ControlWay{SoftUART{}});

    m_DeviceList.print_me();
  while (1)
  {
  }
}

