#ifndef CURSPP_GRAPHICS_PIXEL_TREE_H
#define CURSPP_GRAPHICS_PIXEL_TREE_H

#include <string>

namespace curspp::graphics
{

static const std::string pixel_tree[2][2][2][2] =
{
    { // TOP LEFT 0
        { //TOP RIGHT 0
            { // BOT LEFT 0
                { // BOT RIGHT 0
                        " "
                },
                { // BOT RIGHT 1
                        "⠠"
                }
            },
            { // BOT LEFT 1
                { // BOT RIGHT 0
                        "⠄"
                },
                { // BOT RIGHT 1
                        "⠤"
                }
            }
        },
        { // TOP RIGHT 1
            { // BOT LEFT 0
                { // BOT RIGHT 0
                        "⠈"
                },
                { // BOT RIGHT 1
                        "⠨"
                }
            },
            { // BOT LEFT 1
                { // BOT RIGHT 0
                        "⠌"
                },
                { // BOT RIGHT 1
                        "⠬"
                },
            }
        }
    },
    { // TOP LEFT 1
        { // TOP RIGHT 0
            { // BOT LEFT 0
                { // BOT RIGHT 0
                        "⠁"
                },
                { // BOT RIGHT 1
                        "⠡"
                }
            },
            { // BOT LEFT 1
                { // BOT RIGHT 0
                        "⠅"
                },
                { // BOT RIGHT 1
                        "⠥"
                }
            }
        },
        { // TOP RIGHT 1
            { // BOT LEFT 0
                { // BOT RIGHT 0
                        "⠉"
                },
                { // BOT RIGHT 1
                        "⠩"
                }
            },
            { // BOT LEFT 1
                { // BOT RIGHT 0
                        "⠍"
                },
                { // BOT RIGHT 1
                        "⠭"
                }
            }
        }
    }
};

}

#endif // CURSPP_GRAPHICS_PIXEL_TREE_H
