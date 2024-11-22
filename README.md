# NodeBearingVectorSystem

## Component
### Vector3
Vector3 is the basic format for vector components; NodeVector and BearingVector

float x, y, z;
Vector3(x, y, z);

### NodeVector
NodeVetor work simuler as vectex, 

int index;
Vector3 vec;

NodeVector node(index, vec);

### BearingVector
BearingVector make control point

NodeVector node(index, vec);
Vector3 force;
Vector3 vec;

BearingVector(node, force, vec);

## License
This project is Dual Licensed:

### GNU General Public License v3.0 (GPL 3.0)
Redistribution and modification are permitted under the terms of the GPL 3.0 as published by the Free Software Foundation.
A copy of the GPL 3.0 is provided in LICENSE-GPLv3.txt.

### Commercial License
For commercial use, please contact to obtain a commercial license.
A copy of the Commercial License is provided in LICENSE-Commercial.txt.