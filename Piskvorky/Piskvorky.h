// Piskvorky.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#define PLAYER_NAME_SIZE	20
#define VERT                179 // │ 
#define HORIZ               196 // ─ 
#define UPPER_LEFT_CORNER   218 // ┌ 
#define UPPER_RIGHT_CORNER  191 // ┐ 
#define LOWER_LEFT_CORNER   192 // └ 
#define LOWER_RIGHT_CORNER  217 // ┘ 

#define SS2	P[x - 1][y] == P[x    ][y] && P[x    ][y] == P[x + 1][y]
#define SL  P[x - 2][y] == P[x - 1][y] && P[x - 1][y] == P[x    ][y]
#define SP  P[x    ][y] == P[x + 1][y] && P[x + 1][y] == P[x + 2][y]

#define SS1 P[x][y+1] == P[x][y    ] && P[x][y    ] == P[x][y-1]
#define SD  P[x][y+2] == P[x][y + 1] && P[x][y + 1] == P[x][y  ]
#define	SH  P[x][y-2] == P[x][y - 1] && P[x][y - 1] == P[x][y  ]

#define HS  P[x - 1][y - 1] == P[x    ][y    ] && P[x    ][y    ] == P[x + 1][y + 1]
#define HH  P[x - 2][y - 2] == P[x - 1][y - 1] && P[x - 1][y - 1] == P[x    ][y    ]
#define HD  P[x    ][y    ] == P[x + 1][y + 1] && P[x + 1][y + 1] == P[x + 2][y + 2]

#define VS  P[x - 1][y + 1] == P[x    ][y    ] && P[x    ][y    ] == P[x + 1][y - 1]
#define VD  P[x - 2][y + 2] == P[x - 1][y + 1] && P[x - 1][y + 1] == P[x    ][y    ]
#define VH  P[x    ][y    ] == P[x + 1][y - 1] && P[x + 1][y - 1] == P[x + 2][y - 2]
//static int vyhra;
#include <iostream>

// TODO: Reference additional headers your program requires here.
