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

#include "Constants.h"
#include "subsystems/CustomGyro.h"
#include "subsystems/Limelight.h"
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>
#include <frc/Encoder.h>
#include <frc/Filesystem.h>
#include <frc/controller/PIDController.h>
#include <frc/controller/RamseteController.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/kinematics/ChassisSpeeds.h>
#include <frc/kinematics/DifferentialDriveOdometry.h>
#include <frc/motorcontrol/MotorControllerGroup.h>
#include <frc/motorcontrol/VictorSP.h>
#include <frc/simulation/DifferentialDrivetrainSim.h>
#include <frc/simulation/EncoderSim.h>
#include <frc/smartdashboard/Field2d.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/trajectory/TrajectoryUtil.h>
#include <frc2/command/Command.h>
#include <frc2/command/InstantCommand.h>
#include <frc2/command/PIDCommand.h>
#include <frc2/command/ParallelRaceGroup.h>
#include <frc2/command/RamseteCommand.h>
#include <frc2/command/RunCommand.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/SubsystemBase.h>

#include <frc/trajectory/TrajectoryConfig.h>
#include <frc/trajectory/TrajectoryGenerator.h>
#include <frc/trajectory/TrajectoryUtil.h>
#include <frc/trajectory/constraint/DifferentialDriveVoltageConstraint.h>

#include <rev/CANSparkMax.h>
#include <wpi/fs.h>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace frc2;
using namespace frc;
using namespace rev;
using namespace std;

namespace TD
{
	namespace DrivetrainTypes
	{
		typedef CANSparkMax NEO;
		typedef VictorSP CLASSIC;
		typedef ctre::phoenix::motorcontrol::can::WPI_VictorSPX SPX;
	}

	template <class T>
	class Drivetrain : public SubsystemBase
	{
	public:
		/**
		 * @brief Construct a new Drivetrain object with only motors
		 * @param frontRight The CAN ID or PWM port of the front right motor
		 * @param frontLeft The CAN ID or PWM port of the front left motor
		 * @param backRight The CAN ID or PWM port of the back right motor
		 * @param backLeft The CAN ID or PWM port of the back left motor
		 */
		Drivetrain(unsigned int, unsigned int, unsigned int, unsigned int);

		/**
		 * @brief Construct a new Drivetrain object with motors and encoders
		 * @param frontRight The CAN ID or PWM port of the front right motor
		 * @param frontLeft The CAN ID or PWM port of the front left motor
		 * @param backRight The CAN ID or PWM port of the back right motor
		 * @param backLeft The CAN ID or PWM port of the back left motor
		 * @param frontRightEncoderA The DIO port of the front right encoder A
		 * @param frontRightEncoderB The DIO port of the front right encoder B
		 * @param frontLeftEncoderA The DIO port of the front left encoder A
		 * @param frontLeftEncoderB The DIO port of the front left encoder B
		 */
		Drivetrain(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

		void Periodic() override;

		// --------------------- Actions ----------------------

		/**
		 * @brief Use drivetrain ArcadeDrive to move the chasis
		 * @param speed Speed and direction to move
		 * @param rotation Rotation to turn
		 */
		void Drive(double, double);

		void AutoDrive();

		/**
		 * @brief Reset all systems
		 */
		void ResetSensors();

		/**
		 * @brief Set maximum move and turn speed
		 * @param moveSpeed Maximum speed to move
		 * @param turnSpeed Maximum speed to turn
		 */
		void SetMaxSpeeds(double, double);

		/**
		 * @brief Invert the direction of movement
		 *
		 * @param invert True to invert, false to not
		 */
		void InvertMove(bool invert = true);

		/**
		 * @brief Invert the direction of rotation
		 * @param invert True to invert, false to not
		 */
		void InvertRotation(bool invert = true);

		/**
		 *
		 * @brief Enable drivetrain safety
		 * @param enable True to enable, false to not
		 */
		void SetSafetyEnabled(bool);

		// ---------------------- Motors ----------------------

		/**
		 * @brief Resets motor factory default
		 * @warning Use only once and before everything else
		 */
		void ResetMotors();

		/**
		 * @brief Invert direction of the right motor group
		 * @param invert True to invert, false to not
		 */
		void InvertRight(bool invert = true);

		/**
		 * @brief Invert direction of the left motor group
		 * @param invert True to invert, false to not
		 */
		void InvertLeft(bool invert = true);

		/**
		 * @brief Publishes all motors to the dashboard
		 *
		 */
		void PrintMotors();

		// --------------------- Encoders ---------------------

		/**
		 * @brief Gets the average of the right encoders
		 * @return double average
		 */
		double GetRightEncoders();

		/**
		 * @brief Gets the average of the left encoders
		 * @return double average
		 */
		double GetLeftEncoders();

		/**
		 * @brief Gets the average of the all encoders
		 * @return double average
		 */
		double GetEncoderAverage();

		double GetRightEncodersTotal();

		double GetLeftEncodersTotal();

		/**
		 * @brief Resets the encoders to 0
		 */
		void ResetEncoders();

		/**
		 * @brief Invert the direction of the right encoders
		 * @param invert True to invert, false to not
		 */
		void InvertRightEncoders(bool invert = true);

		/**
		 * @brief Invert the direction of the left encoders
		 * @param invert True to invert, false to not
		 */
		void InvertLeftEncoders(bool invert = true);

		/**
		 * @brief Publish the value of the encoders to the dashboard
		 */
		void PrintEncoders();

		/**
		 * @brief Sets the encoders' distance per revolution
		 * @param pcf Position conversion factor
		 */
		void SetPositionConversionFactor(double);

		void SetGyro(CustomGyro<GyroTypes::NAVX> *gyro);

		void SetGyro(CustomGyro<GyroTypes::CLASSIC> *gyro);

		// ----------------------- Auto -----------------------

		/**
		 * @brief Sets the drivetrain to a given heading.
		 * @param distance The desired heading in meters.
		 * @param speed The speed at which to drive.
		 * @return Wether or not the drivetrain is at the desired heading.
		 */
		bool Move(double, double);

		/**
		 * @brief Prints the move PID error to the dashboard
		 */
		void PrintMoveError();

		/**
		 * @brief Resets the Move PID
		 */
		void ResetMovePIDController();

		/**
		 * @brief Configures move auto PID values and tolerance
		 * @param p The proportional value
		 * @param i The integral value
		 * @param d The derivative value
		 * @param tolerance The tolerance value
		 * @param inverted Invert output calculation
		 */
		void ConfigureMovePID(double, double, double, double, bool = false);

		/**
		 * @brief Turns the drievtrain to a given angle.
		 * @param angle The desired angle in degrees.
		 * @param speed The speed at which to turn.
		 * @return Whether or not the drivetrain has reached the desired angle
		 */
		bool Turn(double, double);

		CommandPtr MoveCmd(double distance, double speed);
		CommandPtr TurnCmd(units::angle::degree_t angle, double rotation);
		CommandPtr MoveToCmd(double x, double y, double movementSpeed, double turningSpeed, bool goBackwards = false);

		CommandPtr TurnToAngleCmd(units::angle::degree_t degrees, double speed);

		CommandPtr BalanceRoll(double speed);

		CommandPtr FollowPath(std::string filename, double speed);
		CommandPtr AlignWithLimelightTarget(double speed);
		CommandPtr AlignWithCameraTarget(double speed);

		void SetInitialPosition(double x, double y);

		/**
		 * @brief Prints the turn PID error to the dashboard
		 */
		void PrintTurnError();

		/**
		 * @brief Resets the Turn PID
		 */
		void ResetTurnPIDController();

		/**
		 * @brief Configures turn auto PID values and tolerance
		 * @param p The proportional value
		 * @param i The integral value
		 * @param d The derivative value
		 * @param tolerance The tolerance value
		 * @param inverted Invert output calculation
		 */
		void ConfigureTurnPID(double, double, double, double, bool = false);

		/**
		 * @brief Moves the drivetrain to a given coordinate in meters
		 * @param x The desired x coordinate.
		 * @param y The desired y coordinate.
		 * @param speed The speed at which to drive.
		 * @param turnSpeed The speed at which to turn.
		 * @return Whether or not the drivetrain has reached the desired coordinate.
		 */
		bool MoveTo(double, double, double, double);

		/**
		 * @brief Prints the move to PID error to the dashboard
		 */
		void PrintMoveToError();

		/**
		 * @brief Prints the current coordinates to the dashboard
		 */
		void PrintCurrentPosition();

		/**
		 * @brief Set drivetrain to a specific angle from the target
		 * @param angle The angle to the target in degrees.
		 * @param speed The speed at which to drive.
		 * @return Whether or not the drivetrain has reached the desired angle
		 */
		bool SetAngleWithTarget(double, double);

		/**
		 * @brief Align chasis to target
		 * @param speed The speed at which to drive.
		 * @return Whether or not the drivetrain has aligned to the target.
		 */
		bool AlignWithTarget(double);

		/**
		 * @brief Prints the align PID error to the dashboard
		 */
		void PrintAlignError();

		/**
		 * @brief Resets the Align with target PID
		 */
		void ResetAlignPIDController();

		/**
		 * @brief Configures align PID values, tolerance and direction
		 * @param p The proportional value
		 * @param i The integral value
		 * @param d The derivative value
		 * @param tolerance The tolerance value
		 * @param inverted Invert output calculation
		 */
		void ConfigureAlignPID(double, double, double, double, bool = false);

		/**
		 * @brief Set drivetrain to a specific distance from the target
		 * @param targetHeight The height from the floor to the center of the target
		 * @param distance The distance to the target in meters.
		 * @param speed The speed at which to drive.
		 * @return Whether or not the drivetrain has reached the desired distance
		 */
		bool SetDistanceWithTarget(double, double, double);

		/**
		 * @brief Prints the distance PID error to the dashboard
		 */
		void PrintSetDistanceError();

		/**
		 * @brief Resets the Distance to target PID
		 */
		void ResetDistancePIDController();

		/**
		 * @brief Configures distance PID values and tolerance
		 * @param p The proportional value
		 * @param i The integral value
		 * @param d The derivative value
		 * @param tolerance The tolerance value
		 * @param inverted Invert output calculation
		 */
		void ConfigureDistancePID(double, double, double, double, bool = false);

		/**
		 * @brief Configures balance PID values and tolerance
		 * @param p The proportional value
		 * @param i The integral value
		 * @param d The derivative value
		 * @param tolerance The tolerance value
		 * @param inverted Invert output calculation
		 */
		void ConfigureBalancePID(double, double, double, double, bool = false);

		/**
		 * @brief Get the absolute angle from a coordinate independent of quadrant
		 * @param x The x coordinate
		 * @param y The y coordinate
		 * @return double the angle
		 */
		double GetAbsoluteAngle(double, double);

		/**
		 * @brief Resets all PID controllers
		 */
		void ResetPIDControllers();

		// ----- Odometry -----

		/**
		 * @brief Configures the odometry object for position estimation
		 * @param startingPose the starting position of the robot
		 */
		void SetPose(Pose2d);

		void UpdatePose();

		void ResetPose();

		Pose2d GetPose();

		void PrintPose();

		using Velocity =
			units::compound_unit<units::meters, units::inverse<units::seconds>>;
		using Acceleration =
			units::compound_unit<Velocity, units::inverse<units::seconds>>;
		using kv_unit = units::compound_unit<units::volts, units::inverse<Velocity>>;
		using ka_unit =
			units::compound_unit<units::volts, units::inverse<Acceleration>>;
		using b_unit =
			units::compound_unit<units::squared<units::radians>,
								 units::inverse<units::squared<units::meters>>>;
		using zeta_unit = units::inverse<units::radians>;

		// ----- Follow path -----

		DifferentialDriveWheelSpeeds GetWheelSpeeds();

		void TankDriveVolts(units::volt_t left, units::volt_t right);

		void ConfigurePathFollower(units::unit_t<b_unit>,
								   units::unit_t<zeta_unit>,
								   units::volt_t,
								   units::unit_t<kv_unit>,
								   units::unit_t<ka_unit>, double, double);

		// ----- Motors -----

		T *m_frontLeft;

		T *m_frontRight;

		T *m_backLeft;

		T *m_backRight;

		// ----- Motor controller groups-----

		MotorControllerGroup *m_right;

		MotorControllerGroup *m_left;

		// ----- Chasis drive object -----

		DifferentialDrive *m_drive;

		// ----- Sensors -----

		SparkMaxRelativeEncoder *m_frontRightEncoder;

		SparkMaxRelativeEncoder *m_frontLeftEncoder;

		SparkMaxRelativeEncoder *m_backRightEncoder;

		SparkMaxRelativeEncoder *m_backLeftEncoder;

		Encoder *m_rightEncoder;

		Encoder *m_leftEncoder;

		// ----- Auto -----

		PIDController m_movePIDController{0.1, 0, 0};

		PIDController m_turnPIDController{0.1, 0, 0};

		PIDController m_alignPIDController{0.1, 0, 0};

		PIDController m_distancePIDController{0.1, 0, 0};

		PIDController m_balancePIDController{0.1, 0, 0};

		CustomGyroBase *m_gyro;

	protected:
		// Limelight m_limelight = Limelight::GetInstance();

		// ----- Attributes -----s

		int m_rightEncodersDirection = 1;

		int m_leftEncodersDirection = 1;

		int m_moveDirection = 1;

		int m_rotationDirection = 1;

		int m_movePIDDirection = 1;

		int m_turnPIDDirection = 1;

		int m_alignPIDDirection = 1;

		int m_distancePIDDirection = 1;

		int m_balancePIDDirection = 1;

		double m_currentX = 0;

		double m_currentY = 0;

		double m_maxMoveSpeed = 1;

		double m_maxTurnSpeed = 1;

		bool m_reachedAngle = false;

		double m_rightEncodersTotal = 0;

		double m_leftEncodersTotal = 0;

		// ---- Kinematics ----

		Pose2d m_pose;

		Field2d m_field;

		Trajectory m_path;

		DifferentialDriveOdometry m_odometry{Rotation2d{}, 0_m, 0_m};

		// ----- Path follower -----
		units::unit_t<b_unit> m_pathB = 0_rad * 0_rad / (1_m * 1_m);
		units::unit_t<zeta_unit> m_pathZeta = 0 / 1_rad;
		units::volt_t m_pathKs = 0_V;
		units::unit_t<kv_unit> m_pathKv = 0_V * 0_s / 1_m;
		units::unit_t<ka_unit> m_pathKa = 0_V * 0_s * 0_s / 1_m;
		double m_pathRightP = 8.5;
		double m_pathLeftP = 8.5;

		double m_autoMoveOutput = 0;
		double m_autoTurnOutput = 0;
	};

}