# TODO
- [ ] Cellular physics
  - split area into cells 
  - only the cells near the camera are simulated
- [x] transform system
- [x] ~~Add parent GameObject which has children~~
- [x] more shapes
- [x] materials
- [x] improve collision detection efficiency
  - chugs when there are more than a few objects
  - improved with bigger physics timedelta
- [x] free object collisions
- [x] physics engine tests
- [x] force fields
- [x] physics engine separate to game logic
- [x] tests

## Games
- procedurally generated solar system

## Bugs

- [x] Free objects placed at start, disappear
  - reckon its due to non-initialised force vector
  - initialised force vector to zero; will see if this is fixed
- [x] Objects fall through lines near edge
  - possibly related to normal calculated on half-circle
  - ~~solve by improving normal calculation on bounds~~
  - solved by fixing edge-of-range collision detection
- [x] Polygons break through bounds occasionally
  - can't have broken polygon physics if there aren't polygons!
