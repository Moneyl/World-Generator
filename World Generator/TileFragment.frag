uniform vec4 DefBaseColor;
uniform vec4 DefForeColor;

uniform vec4 BaseColor;
uniform vec4 ForeColor;

uniform sampler2D TileTexture;

void main()
{
    vec4 Pixel = texture2D(TileTexture, gl_TexCoord[0].st);

	if(all(equal(Pixel, DefBaseColor)))
		Pixel = BaseColor;
	
	if(all(equal(Pixel, DefForeColor)))
		Pixel = ForeColor;
	
	gl_FragColor = Pixel;
}