# RayTracing

Practice with [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html). This is a pure CPU ray tracer.
Features

  -  materials: dielectric, metal, Lambertian
  -  depth of field

## Result

- 192 small spheres + 3 major spheres + 1 sphere for ground.  

- Apple M1 Pro, 16 GB, 8 Cores (6 performance and 2 efficiency)

- image size = (600, 337)

### Brute force

<img width="600" alt="image" src="https://github.com/MiaZhengLS/RayTracing/assets/121979781/17c9d99d-2e4a-45b9-acd1-577261a615d9">

Center glass ball solid (Brute force)

- samples per pixel = 100

- time taken = 7m16s

<img width="600" alt="image" src="https://github.com/MiaZhengLS/RayTracing/assets/121979781/d422bade-70a6-4ac7-8451-85a213b1f12c">

Center glass ball hollow (actually this one has 4 major balls)

- samples per pixel = 20

- time taken = 2m13s

### With BVH

<img width="600" alt="image" src="https://github.com/MiaZhengLS/RayTracing/assets/121979781/5eb9bfea-9b63-4ccc-9366-71f92caa113a">

Center glass ball hollow (actually this one has 4 major balls)

- samples per pixel = 100

- **time taken = 3m55s**
