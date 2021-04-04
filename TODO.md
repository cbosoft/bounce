# TODO

- [ ] materials
    - [ ] friction
    - [ ] bounciness
- [ ] more shapes
    - [ ] rectangles
    - [ ] triangles
    - [ ] regular polygons
- [ ] transform system
- [x] free object collisions
- [x] physics engine tests
- [x] force fields
- [x] physics engine separate to game logic
- [x] tests

## Bugs

- [ ] Free objects placed at start, disappear
  - reckon its due to non-initialised force vector
  - initialised force vector to zero; will see if this is fixed
- [ ] Objects fall through lines near edge
  - possibly related to normal calculated on half-circle
  - solve by improving normal calculation on bounds
