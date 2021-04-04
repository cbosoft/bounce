# TODO
- [ ] transform system
  - [x] basic structure
  - [ ] transform represented by transformation matrices
- [ ] Add parent GameObject which has children:
  - PhysicsObject
  - GeometricEquation(s)
  - RenderableObject
- [x] more shapes
  - [ ] ~~rectangles~~
  - [ ] ~~triangles~~
  - [x] regular polygons
- [x] materials
  - [ ] ~~friction~~
  - [x] bounciness
- [x] improve collision detection efficiency
  - chugs when there are more than a few objects
  - improved with bigger physics timedelta
- [x] free object collisions
- [x] physics engine tests
- [x] force fields
- [x] physics engine separate to game logic
- [x] tests

## Bugs

- [ ] Free objects placed at start, disappear
  - reckon its due to non-initialised force vector
  - initialised force vector to zero; will see if this is fixed
- [x] Objects fall through lines near edge
  - possibly related to normal calculated on half-circle
  - ~~solve by improving normal calculation on bounds~~
  - solved by fixing edge-of-range collision detection
- [ ] Polygons break through bounds occasionally
