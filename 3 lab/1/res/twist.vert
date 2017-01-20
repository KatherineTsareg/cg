void main()
{
	float newY = sin(gl_Vertex.x) / gl_Vertex.x;
    vec4 twistedCoord = vec4(
        gl_Vertex.x,
        newY,
        gl_Vertex.z,
		gl_Vertex.w
    );
    vec4 position = gl_ModelViewProjectionMatrix * twistedCoord;
    gl_Position = position;
    gl_FrontColor = vec4(1.f, 0.f, 0.f, 1.f);
}