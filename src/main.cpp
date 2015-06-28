#include <ode/ode.h>
#include <drawstuff/drawstuff.h>
#ifdef dDOUBLE
#define dsDrawSphere dsDrawSphereD
#endif

static dWorldID world;
static dSpaceID space;

struct PCatLeg {
  dBodyID b_top;
  dGeomID g_top;

  dBodyID b_thigh;
  dGeomID g_thigh;
};

struct PCat {
  dBodyID b_spine;
  dGeomID g_spine;
  dMass m_spine;

  PCatLeg front_left_leg;
  PCatLeg front_right_leg;
  PCatLeg back_left_leg;
  PCatLeg back_right_leg;
};

static PCat cat;

static dJointGroupID contactgroup;

static void nearCallback (void *data, dGeomID o1, dGeomID o2) {
  /* dBodyID b1 = dGeomGetBody(o1); */
  /* dBodyID b2 = dGeomGetBody(o2); */
  /* dContact contact; */
  /* contact.surface.mode = dContactBounce | dContactSoftCFM; */
  /* // friction parameter */
  /* contact.surface.mu = dInfinity; */
  /* // bounce is the amount of "bouncyness". */
  /* contact.surface.bounce = 0.9; */
  /* // bounce_vel is the minimum incoming velocity to cause a bounce */
  /* contact.surface.bounce_vel = 0.1; */
  /* // constraint force mixing parameter */
  /* contact.surface.soft_cfm = 0.001; */
  /* if (int numc = dCollide (o1,o2,1,&contact.geom,sizeof(dContact))) { */
  /*   dJointID c = dJointCreateContact (world,contactgroup,&contact); */
  /*   dJointAttach (c,b1,b2); */
  /* } */
}

// start simulation - set viewpoint
static void start() {
  static float xyz[3] = {2.0f,-2.0f,1.7600f};
  static float hpr[3] = {140.000f,-17.0000f,0.0000f};
  dsSetViewpoint (xyz,hpr);
}
// simulation loop
static void simLoop (int pause) {
  /* const dReal *pos; */
  /* const dReal *R; */
  // find collisions and add contact joints
  dSpaceCollide(space, 0, &nearCallback);
  // step the simulation
  dWorldStep (world, 0.02);
  // remove all contact joints
  dJointGroupEmpty (contactgroup);

  /* pos = dGeomGetPosition (geom); */
  /* R = dGeomGetRotation (geom); */

  const double sides[3] = {20.225, 20.085, 20.2};

  dsDrawBoxD(
    dGeomGetPosition(cat.g_spine),
    dGeomGetRotation(cat.g_spine),
    sides
  );
}

int main (int argc, char **argv) {
  dsFunctions fn;
  fn.version = DS_VERSION;
  fn.start = &start;
  fn.step = &simLoop;
  fn.stop = 0;
  fn.command = 0;
  fn.path_to_textures = "textures";

  dInitODE ();
  // create world
  world = dWorldCreate ();
  space = dHashSpaceCreate (0);
  dWorldSetGravity (world,0,0,-0.81);
  dWorldSetCFM (world,1e-5);
  dCreatePlane (space,0,0,1,0);
  contactgroup = dJointGroupCreate (0);
  // create object
  cat.b_spine = dBodyCreate (world);
  cat.g_spine = dCreateBox(space, 0.255, 0.085, 0.001);
  dMassSetBox(&cat.m_spine, 1, 0.255, 0.085, 0.001);
  dBodySetMass(cat.b_spine, &cat.m_spine);
  dGeomSetBody(cat.g_spine, cat.b_spine);
  /* // set initial position */
  dBodySetPosition(cat.b_spine, 0, 0, 30);
  // run simulation
  dsSimulationLoop(argc, argv, 352, 288, &fn);
  // clean up
  dJointGroupDestroy (contactgroup);
  dSpaceDestroy (space);
  dWorldDestroy (world);
  dCloseODE();
  return 0;
}
