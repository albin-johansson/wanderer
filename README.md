# Wanderer 

[![version](https://img.shields.io/badge/version-0.1.0-blue.svg)](https://semver.org)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![Language](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) 
[![CI: Windows](https://github.com/albin-johansson/wanderer/actions/workflows/windows.yml/badge.svg?branch=dev)](https://github.com/albin-johansson/wanderer/actions/workflows/windows.yml)

Wanderer is an 2D indie game, being developed for fun. At the time of writing, the game is still in an experimental state and isn't ready to be played. This project also serves as a "tech demo" for the Centurion library, which is also developed by me.

## Compatibility

Wanderer is developed using MSVC, intended to run on Windows machines. As a result, the codebase occasionally takes
advantage of minor non-standard improvements of the STL found in the MSVC STL implementation, such as better `noexcept` coverage. Other than that, the code should be platform independent.
