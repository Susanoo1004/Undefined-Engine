#version 450 core


// Ouput data
out int color;

// Values that stay constant for the whole mesh.
uniform int PickingColor;

void main()
{
    color = PickingColor;
}