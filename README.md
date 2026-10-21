# University Projects

Coursework, research schools and reports from my BSc in Physics and Astronomy (2016–2019) and MSc in Computational
Science (2019–2021) at the University of Oslo. The work is mostly numerical simulation and data analysis in C++ and Python.

My MSc thesis has its own repository: [msc-thesis-lfp](https://github.com/steinnhauser/msc-thesis-lfp).

| Folder | Context | Year | Tech | What it is |
| --- | --- | --- | --- | --- |
| [`fys3150/`](fys3150/) | FYS3150 Computational Physics, UiO | 2018 | C++, Armadillo, Python | Five projects on core numerical methods (below), with reports in [`fys3150/Reports/`](fys3150/Reports/). Written with Simen Haapnes. |
| [`neural-networks/`](neural-networks/) | FYS-STK4155 Applied Data Analysis and Machine Learning, UiO | 2019 | Python, NumPy, scikit-learn, TensorFlow, XGBoost | A multilayer perceptron with backpropagation written from scratch and applied to credit card default data. Also regression on real terrain data and an XGBoost study on Extended MNIST. |
| [`4dsnw-kobe-2019/`](4dsnw-kobe-2019/) | 4D Space Numerical Workshop, Kobe University | 2019 | Particle-in-cell plasma simulation, HDF5 | A team project run on the Kobe University supercomputer. We simulated the floating potential on the NORSAT-1 satellite's Langmuir probes for ionospheres dominated by H, He, O and Ar ions. Run outputs and the presentation are included. |
| [`swss-boston-2018/`](swss-boston-2018/) | Space Weather Science School, Boston | 2018 | Python | Analysis of solar wind and geomagnetic data from ACE, STEREO-B, THEMIS and DST, provided by NOAA. |
| [`bsc-reports/`](bsc-reports/) | BSc coursework, UiO | 2017–2019 | Python, Numba | AST2000 astrophysics reports (solar system, rocket engine, data analysis), FYS2130 and FYS2140 projects, and a Mandelbrot package with pure-Python, NumPy and Numba implementations. |

### FYS3150 projects

1. **Poisson's equation in 1D**: Thomas algorithm versus LU decomposition
2. **Eigenvalue problems**: Jacobi rotation for the buckling beam and for two electrons in a harmonic oscillator well
3. **Solar system in 3D**: object-oriented N-body simulation with the velocity Verlet method
4. **2D Ising model**: Metropolis Monte Carlo and phase transitions
5. **Heat diffusion in the lithosphere**: explicit, implicit and Crank–Nicolson schemes in 1D and 2D

## History

This repository started as `FYS3150` and was later renamed. The other folders were merged in from their own repositories
(`Neural-Networks`, `Project-Reports`, `SWSS-Boston-2018`, `4DSNW-2019`) with all their commits kept.
`git log --follow <file>` shows a file's history from before the move.

## Credits

- FYS3150 was written together with [Simen Haapnes](https://github.com/simehaa), who also contributed to `neural-networks/`.
- The 4DSNW "Friendly Ions" team: Jessie Warraich, Azumi Nawata, Miho Okamura and Shuji Doi. The floating potential lecture in that folder is by one of the workshop lecturers.
- Space weather data in `swss-boston-2018/` is from [NOAA SWPC](https://www.swpc.noaa.gov/).
