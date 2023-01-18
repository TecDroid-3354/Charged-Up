/*------------------------------------------------------------
						&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& /&&&&,
					.&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& /&&&&&&&&%
				.&&&&/ &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& /&&&&&&&&&&&*
			.%&&&(      &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&% %&&&&&&&&&&&&&
		%&&&#     %#&&#           (&&&&&&&&&&&              %&&&&&&&&&&&&&
	*&&&#                          (&&&&&&&&&&&    /           %&&&&&&&&&&&
*&%  ,                           (&&&&&&&&&&&(&&&&(           &&&&&&&&&&&
& (,..                          (&&&&&&&&&&&&&&&&            %&&&&&&&&&&
	&*                             (&&&&&&&&&&&&&&&&            &&&&&&&&&&&
	&/                             (&&&&&&&&&&&&&&&&%          &&&&&&&&&&&(
	#&&    .&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&#**(&&&&&&&&&&&&&#
	&#  (&                        ......... &&&&&&&&&&&&&&&&&&&&&&&&&&
	/&   &                                   .&&&&&&&&&&&&&&&&&&&&&&
		%&&* &*                                   ,%&&&&&&&&&&&&&%*

	Author: Esteban Padilla Cerdio
	Email: esteban37padilla@gmail.com
	URL: github.com/esteb37
		 github.com/tecdroid-3354
	Date: 12/04/2022
	Language: cpp
	Copyright (c) TecDroid 3354 and Esteban Padilla Cerdio
	Open Source Software; you can modify and/or share it under the terms of
*/

#pragma once

#include "subsystems/MotorSubsystemBase.h"
#include "subsystems/SolenoidSubsystemBase.h"

namespace TD
{
	template <class T>
	class IntakeBase : public MotorSubsystemBase<T>, public SolenoidSubsystemBase
	{

	public:
		IntakeBase();

		/**
		 * @brief Construct a new Intake object with a single motor and a single solenoid
		 *
		 * @param motorPort The motor port
		 * @param solenoidForward The solenoid forward port
		 * @param solenoidReverse The solenoid reverse port
		 */
		IntakeBase(unsigned int, unsigned int, unsigned int);

		/**
		 * @brief Construct a new Intake object with multiple motors and a single solenoid
		 *
		 * @param motorPorts The motor ports
		 * @param solenoidForward The solenoid forward port
		 * @param solenoidReverse The solenoid reverse port
		 */
		IntakeBase(vector<unsigned int>, unsigned int, unsigned int);

		/**
		 * @brief Construct a new Intake object with a single motor and multiple solenoids
		 *
		 * @param motorPort The motor port
		 * @param rightSolenoidForward The right solenoid forward port
		 * @param rightSolenoidReverse The right solenoid reverse port
		 * @param leftSolenoidForward The left solenoid forward port
		 * @param leftSolenoidReverse The left solenoid reverse port
		 */
		IntakeBase(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

		/**
		 * @brief Construct a new Intake object with multiple motors and multiple solenoids
		 *
		 * @param motorPorts The motor ports
		 * @param rightSolenoidForward The right solenoid forward port
		 * @param rightSolenoidReverse The right solenoid reverse port
		 * @param leftSolenoidForward The left solenoid forward port
		 * @param leftSolenoidReverse The left solenoid reverse port
		 */
		IntakeBase(vector<unsigned int>, unsigned int, unsigned int, unsigned int, unsigned int);

		void Periodic() override;

		// ---------- Actions -----------

		/**
		 * @brief Turns the intake inward
		 */
		void Take();

		/**
		 * @brief Turns the intake outward
		 */
		void Spit();

		/**
		 * @brief Lower the intake with solenoids
		 */
		void Lower();

		/**
		 * @brief Raise the intake with solenoids
		 */
		void Raise();
	};
}