#include "pdg/sys/physicsbody.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <stdexcept>
using namespace pdg;
namespace {
int checks=0;
void expect(bool ok,const char* message) {++checks;if(!ok)throw std::runtime_error(message);}
void near(double actual,double expected,const char* message,double tolerance=1e-9) {
    if (!std::isfinite(actual) || std::abs(actual-expected)>tolerance) {
        std::cerr<<message<<": "<<actual<<" expected "<<expected<<'\n';throw std::runtime_error(message);
    }
    ++checks;
}
template<class F> void rejects(F fn) {try{fn();}catch(const std::exception&){++checks;return;}expect(false,"invalid value accepted");}
void loads() {
    PhysicsBody body(2,4);
    body.applyImpulse(Vector(8,-4));near(body.getState().velocityX,4,"linear impulse divided by mass");
    body.applyAngularImpulse(8);near(body.getAngularVelocity(),2,"angular impulse divided by inertia");
    near(body.getAngularMomentum(),8,"angular momentum");
    body.applyForce(Vector(4,0),.25,.125);body.applyTorque(8,.25,.125);
    body.step(.5);near(body.getState().velocityX,4.5,"force exact lifetime");
    near(body.getState().x,2.125,"delayed force displacement plus tail");
    near(body.getState().y,-1,"free motion");
    near(body.getState().rotation,1.125,"delayed torque displacement plus tail");
    near(body.getAngularVelocity(),2.5,"timed torque exact lifetime");
    body.applyForce(Vector(999,0),0);body.applyTorque(999,0);body.step(.5);
    near(body.getState().velocityX,4.5,"zero force duration is no impulse");
    near(body.getAngularVelocity(),2.5,"zero torque duration is no angular impulse");
    const auto force=body.addContinuousForce(Vector(2,0));body.step(.25);
    near(body.getState().velocityX,4.75,"continuous force integrates");
    expect(body.removeForce(force),"force cancellation succeeds");expect(!body.removeForce(force),"force cancellation idempotent");
    body.step(.25);near(body.getState().velocityX,4.75,"cancelled force stops applying");
    PhysicsBody point(2,4);point.teleport(Point(10,20),0);
    point.applyImpulse(Vector(0,8),Point(13,20));
    near(point.getState().velocityY,4,"off-center linear impulse");near(point.getAngularVelocity(),6,"off-center angular impulse");
    point.applyForce(Vector(0,8),Point(13,20),.5);point.step(.5);
    near(point.getAngularVelocity(),9,"off-center torque");
}
void damping() {
    PhysicsBody coarse(2,4),fine(2,4);
    for(auto* body:{&coarse,&fine}) {
        body->setVelocity(Vector(10,-3)).setAngularVelocity(4).setLinearDamping(.7).setAngularDamping(.2);
        body->applyForce(Vector(6,2),.375,.125);body->applyForce(Vector(-2,0),.25,.25);
        body->applyTorque(-8,.625);body->addContinuousForce(Vector(1,0));
    }
    coarse.step(1);for(int i=0;i<100;++i)fine.step(.01);
    const auto a=coarse.getState(),b=fine.getState();
    near(a.x,b.x,"linear displacement partition independence");near(a.y,b.y,"y partition independence");
    near(a.rotation,b.rotation,"angular displacement partition independence");
    near(a.velocityX,b.velocityX,"velocity partition independence");near(a.angularVelocity,b.angularVelocity,"angular velocity partition independence");
    PhysicsBody free(1,1);free.setVelocity(Vector(10,0)).setLinearDamping(2);free.step(.5);
    near(free.getState().velocityX,10*std::exp(-1),"physical exponential damping");
    near(free.getState().x,5*(1-std::exp(-1)),"damped displacement");
    PhysicsBody tiny(1,1);tiny.applyForce(Vector(1,0),.00000025);tiny.step(.0000005);
    near(tiny.getState().velocityX,.00000025,"submicrosecond lifetime",1e-15);
    near(tiny.getState().x,9.375e-14,"submicrosecond displacement",1e-20);
}
void drives() {
    PhysicsBody body(2,4);
    body.setDriveTarget(Point(100,100),10,6,8,4,1,rotationDirection_AsSpecified);
    near(body.getState().x,0,"setting a drive never teleports");
    body.step(.25);
    expect(body.getSpeed() <= .75+1e-9,"linear drive impulse respects vector force limit");
    expect(std::abs(body.getAngularVelocity()) <= .5+1e-9,"angular drive impulse respects torque and inertia");
    const auto drive=body.getDriveState();
    near(std::hypot(drive.forceX,drive.forceY),6,"drive force clamps vector magnitude");
    near(drive.torque,8,"drive torque clamps independently");
    rejects([&]{body.setDriveTarget(Point(0,0),0,-1,2);});
    rejects([&]{body.setDriveTarget(Point(0,0),0,1,2,0);});
    rejects([&]{body.setDriveTarget(Point(0,0),0,1,2,4,-1);});
    rejects([&]{body.setDriveTarget(Point(0,0),0,1,2,4,1,42);});
    near(body.getDriveState().x,100,"invalid drive edit preserves previous target");
    const auto speed=body.getSpeed();body.clearDrive();body.step(.1);
    expect(!body.isDriveEnabled(),"clearDrive removes controller");near(body.getSpeed(),speed,"clearDrive preserves momentum");
    for (int direction : {rotationDirection_AsSpecified,rotationDirection_Shortest,
                          rotationDirection_Clockwise,rotationDirection_CounterClockwise}) {
        PhysicsBody turned;turned.teleport(Point(0,0),.2);
        turned.setDriveTarget(Point(0,0),-.2,0,100,4,1,direction);
        expect((turned.getDriveState().rotation>.2)==(direction==rotationDirection_Clockwise),"directed drive route");
        turned.step(.01);
        expect((turned.getAngularVelocity()>0)==(direction==rotationDirection_Clockwise),"drive follows selected angular route");
    }
    PhysicsBody settle;
    settle.setDriveTarget(Point(4,-3),1,100,100,2,1);
    for(int i=0;i<240;++i)settle.step(1.0/120.0);
    near(settle.getState().x,4,"basic physical drive converges",1e-4);
    near(settle.getState().y,-3,"basic drive y converges",1e-4);
    near(settle.getState().rotation,1,"basic angular drive converges",1e-4);
    settle.setMode(physicsBody_Kinematic);expect(!settle.isDriveEnabled(),"kinematic transition cancels drive");
    rejects([&]{settle.setDriveTarget(Point(0,0),0,1,1);});
    settle.setMode(physicsBody_Dynamic).setDriveTarget(Point(0,0),0,1,1).stopAllForces();
    expect(!settle.isDriveEnabled(),"stopAllForces cancels active drive");
    auto& none=PhysicsBody::NoPhysics;
    expect(&none.setDriveTarget(Point(1,2),1,10,10)==&none,"NoPhysics drive remains fluent");
    expect(!none.isDriveEnabled() && !none.getDriveState().enabled,"NoPhysics does not store drive targets");
}
void angularSpeedThresholds() {
    PhysicsBody shaft, housing;
    int notifications=0;PhysicsBodyBreakInfo event;
    shaft.setBreakHandler([&](const PhysicsBodyBreakInfo& info){++notifications;event=info;});
    expect(&shaft.setBreakAngularSpeed(10)==&shaft,"threshold setter is fluent");
    shaft.setAngularVelocity(11);shaft.step(0);expect(notifications==0,"zero-duration step does not notify");
    shaft.step(.01);expect(notifications==1,"detached native body reports overspeed");
    near(event.angularSpeed,11,"native callback measures angular speed");
    shaft.step(.01);expect(notifications==1,"one notification per excursion");
    for(double bad:{-1.0,std::numeric_limits<double>::infinity(),std::numeric_limits<double>::quiet_NaN()})
        rejects([&]{shaft.setBreakAngularSpeed(bad);});
    rejects([&]{shaft.setBreakAngularSpeed(2,&shaft);});
    rejects([&]{shaft.setBreakAngularSpeed(2,&PhysicsBody::NoPhysics);});
    near(shaft.getBreakAngularSpeed(),10,"invalid edit leaves threshold unchanged");
    shaft.step(.01);expect(notifications==1,"invalid edit does not rearm monitor");
    shaft.setAngularVelocity(10);shaft.step(.01);shaft.setAngularVelocity(-11);shaft.step(.01);
    expect(notifications==2,"both directions notify after boundary rearm");
    shaft.setBreakAngularSpeed(5,&housing);housing.setAngularVelocity(100);shaft.setAngularVelocity(100);shaft.step(.01);
    expect(notifications==2,"co-rotating body reference does not notify");
    shaft.setAngularVelocity(106);shaft.step(.01);expect(notifications==3 && event.referenceBody==&housing,"relative overspeed without a joint");
    shaft.setBreakAngularSpeed(0);shaft.step(.01);expect(notifications==3 && !shaft.getBreakAngularSpeedReference(),"zero disables and clears reference");
    {
        PhysicsBody reference;
        shaft.setBreakAngularSpeed(1,&reference);
    }
    expect(shaft.getBreakAngularSpeed()==0 && !shaft.getBreakAngularSpeedReference(),"reference destruction safely disables dependent monitors");
    PhysicsBody::NoPhysics.setBreakAngularSpeed(10);
    near(PhysicsBody::NoPhysics.getBreakAngularSpeed(),0,"NoPhysics threshold remains immutable");
    shaft.setMode(physicsBody_Kinematic).setBreakAngularSpeed(1).setAngularVelocity(2);shaft.step(.01);
    expect(notifications==4,"kinematic free angular velocity is monitored");
    shaft.setMode(physicsBody_Dynamic).setAngularVelocity(0);shaft.step(.01);
    shaft.applyTorque(10,.2);shaft.step(.2);
    expect(notifications==5,"acceleration from torque triggers a post-step break");
    near(shaft.getAngularVelocity(),2,"overspeed torque leaves free physical motion unchanged");
}
void modesAndAbsence() {
    auto& none=PhysicsBody::NoPhysics;expect(!none.isPresent(),"NoPhysics absent");
    expect(none.getSolver()==physicsSolver_None,"NoPhysics has no solver");
    none.applyImpulse(Vector(10,20)).applyAngularImpulse(30).setMass(40).setVelocity(Vector(50,60));
    none.applyForce(Vector(1,2),3);none.applyTorque(1,2);none.step(10);
    near(none.getMass(),0,"NoPhysics immutable mass");near(none.getSpeed(),0,"NoPhysics immutable velocity");
    near(none.getState().x,0,"NoPhysics stores no motion");none.addRef();none.release();
    PhysicsBody body(1,1);body.setMode(physicsBody_Kinematic).setVelocity(Vector(2,0));
    body.applyImpulse(Vector(50,0));body.applyForce(Vector(50,0),1);body.step(.5);
    near(body.getState().x,1,"kinematic motion ignores forces");
    body.setMode(physicsBody_Static);body.setVelocity(Vector(50,0));body.step(1);
    near(body.getState().x,1,"static body does not move");near(body.getSpeed(),0,"static velocity stays zero");
    rejects([&]{body.setMode(17);});rejects([&]{body.setMass(0);});rejects([&]{body.setMomentOfInertia(-1);});
    rejects([&]{body.applyTorque(1,-1);});rejects([&]{body.step(-.1);});rejects([&]{body.setLinearDamping(-1);});
    rejects([&]{body.setVelocity(Vector(std::numeric_limits<float>::infinity(),0));});
    rejects([&]{body.applyForce(Vector(1,0),std::numeric_limits<double>::quiet_NaN());});
}
}
int main() {
    try {loads();damping();drives();angularSpeedThresholds();modesAndAbsence();std::cout<<"PhysicsBody contract passed "<<checks<<" assertions\n";}
    catch(const std::exception& error) {std::cerr<<error.what()<<'\n';return EXIT_FAILURE;}
    return EXIT_SUCCESS;
}
