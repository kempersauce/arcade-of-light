#pragma once
// this file holds our shapes for the beats game


namespace kss {
namespace engines {

// ShapeRightArrow
int ShapeRightArrow[8][5] = {{0, 1, 0, 0, 0}, {0, 0, 1, 0, 0}, {1, 0, 0, 1, 0},
                             {0, 1, 0, 0, 1}, {0, 1, 0, 0, 1}, {1, 0, 0, 1, 0},
                             {0, 0, 1, 0, 0}, {0, 1, 0, 0, 0}};

// ShapeLeftArrow
int ShapeLeftArrow[8][5] = {{0, 0, 0, 1, 0}, {0, 0, 1, 0, 0}, {0, 1, 0, 0, 1},
                            {1, 0, 0, 1, 0}, {1, 0, 0, 1, 0}, {0, 1, 0, 0, 1},
                            {0, 0, 1, 0, 0}, {0, 0, 0, 1, 0}};

// ShapeUpArrow
int ShapeUpArrow[8][5] = {{0, 0, 1, 0, 0}, {0, 1, 0, 1, 0}, {1, 0, 0, 0, 1},
                          {0, 0, 1, 0, 0}, {0, 1, 0, 1, 0}, {1, 0, 0, 0, 1},
                          {0, 0, 1, 0, 0}, {0, 1, 0, 1, 0}};

// ShapeDownArrow
int ShapeDownArrow[8][5] = {{0, 1, 0, 1, 0}, {0, 0, 1, 0, 0}, {1, 0, 0, 0, 1},
                            {0, 1, 0, 1, 0}, {0, 0, 1, 0, 0}, {1, 0, 0, 0, 1},
                            {0, 1, 0, 1, 0}, {0, 0, 1, 0, 0}};


}  // namespace engines
}  // namespace kss
