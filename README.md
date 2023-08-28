# RayTracing

Practice with [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html). This is a pure CPU ray tracer using a brute-force approach.

Features

  -  materials: dielectric, metal, Lambertian
  -  depth of field

Result with 192 spheres, Apple M1 Pro, 16 GB, 8 Cores (6 performance and 2 efficiency)

<img width="600" alt="image" src="https://github.com/MiaZhengLS/RayTracing/assets/121979781/17c9d99d-2e4a-45b9-acd1-577261a615d9">

Center glass ball solid

- samples per pixel = 100

- image size = (600, 337)

- time taken = 7m16s

<img width="600" alt="image" src="https://github.com/MiaZhengLS/RayTracing/assets/121979781/d422bade-70a6-4ac7-8451-85a213b1f12c">

Center glass ball hollow (actually this one is 193 balls)

- samples per pixel = 20

- image size = (600, 337)

- time taken = 2m13s
