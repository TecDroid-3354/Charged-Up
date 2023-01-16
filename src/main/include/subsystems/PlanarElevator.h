#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc2/command/CommandPtr.h>

#include "subsystems/ElevatorBase.h"
#include "../utility/Plane.h"
#include "../utility/Vector.h"

namespace TD {
  class PlanarElevator : frc2::SubsystemBase {
    public:

    PlanarElevator() = default;

    void Initialize();

    void Periodic() override;

    double GetX();
    double GetY();

    utility::Point2D GetPosition();

    bool MoveTo(utility::Point2D &point, double speed);
    bool MoveBy(utility::Vector2D &vec, double speed);

    void MoveHorizontally(float amount);
    void MoveVertically(float amount);

    frc2::CommandPtr GotoPositiveX(double speed);
    frc2::CommandPtr GotoPositiveY(double speed);
    frc2::CommandPtr GotoNegativeX(double speed);
    frc2::CommandPtr GotoNegativeY(double speed);

    frc2::CommandPtr CenterHorizontally(double speed);
    frc2::CommandPtr CenterVertically(double speed);

    frc2::CommandPtr GotoTopLeft(double speed);
    frc2::CommandPtr GotoTopRight(double speed);
    frc2::CommandPtr GotoBottomLeft(double speed);
    frc2::CommandPtr GotoBottomRight(double speed);

    frc2::CommandPtr GotoOrigin(double speed);

    private:

    ElevatorBase *xAxis;
    ElevatorBase *yAxis;

    utility::BoundPlane<1> plane = utility::BoundPlane<1>();
    
  };
}