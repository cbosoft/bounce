Bounce Engine    {#mainpage}
=============

A 2D game engine in C++.

A Game is centred around Scene(s). Each Scene is a container for Object(s) and Renderable(s), and accepts input from
the player. Each Scene is actually the root of a tree, with nodes of Transform objects. These nodes in turn hold physics
Object(s) and Renderable(s).

Object collision is handled by the PhysicsEngine singleton, which timesteps objects in-between frame updates to keep
game time in sync with world time, depending on the time-scale.

Rendering is handled by the Renderer: powered by OpenGL, GLEW, and GLFW. The Renderer traverses the active Scene and
pulls out Renderable(s), which are then displayed.

A very simple demo game is implemented in DemoSpaceShooter.