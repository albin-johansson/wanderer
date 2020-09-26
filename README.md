# Wanderer 
[![Build status](https://ci.appveyor.com/api/projects/status/ly6ydfw5uf62lpqg?svg=true)](https://ci.appveyor.com/project/AlbinJohansson/wanderer) [![version](https://img.shields.io/badge/version-0.1.0-blue.svg)](https://semver.org) [![Language](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) [![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://opensource.org/licenses/MIT) ![GitHub repo size](https://img.shields.io/github/repo-size/albin-johansson/Wanderer)

Wanderer is an 2D indie game, being developed for fun. At the time of writing, the game is still in an experimental state and isn't ready to be played.

## Compatibility

Wanderer is developed using MSVC, intended to run on Windows machines. As a result, the codebase occasionally takes
advantage of minor non-standard improvements of the STL found in the MSVC STL implementation, such as better `noexcept` coverage. Other than that, the code should be platform independent.

<p align="middle">
  <img src="meta/screenshot_trees.png" width="45%" />
  <img src="meta/screenshot_plants.png" width="45%"/> 
</p>

## Dependencies

- [Centurion](https://github.com/albin-johansson/Centurion) A multi-media library built on top of SDL2.
- [EnTT](https://github.com/skypjack/entt) An amazing ECS library. One of the best libraries I've ever used!
- [step](https://github.com/albin-johansson/step) A parsing library for the Tiled JSON format. Was originally a part of the Wanderer codebase.
- [json](https://github.com/nlohmann/json) Very well-written JSON library, despite being limited to C++11.

## Acknowledgements

- [SimpleVoxelEngine (James Randall)](https://github.com/JamesRandall/SimpleVoxelEngine) The game makes use of an adapted version of the AABB tree written by James Randall for the Simple Voxel Engine project.
- [Theo Wiik](https://github.com/theowiik) Helped with feedback and ideas.
- [Oscar Almström](https://github.com/oscaralmstrom) Helped with feedback and ideas.