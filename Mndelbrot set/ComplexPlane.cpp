#include "ComplexPlane.h"
#include <cmath>

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
	m_pixel_size.x = pixelWidth;

	m_pixel_size.y = pixelHeight;

	m_aspectRatio = (1.0 * pixelHeight) / (1.0 * pixelHeight);

	m_plane_center.x = 0;

	m_plane_center.y = 0;

	m_plane_size.x = BASE_WIDTH;

	m_plane_size.y = BASE_HEIGHT * m_aspectRatio;

	m_state = State::CALCULATING;

	m_zoomCount = 0;

	m_vArray.setPrimitiveType(Points);

	m_vArray.resize(pixelWidth * pixelHeight);
}
void ComplexPlane::updateRender()
{
	if (m_state == State::CALCULATING)
	{
		for (int j = 0; j < m_pixel_size.x; j++)
		{
			
			for (int i = 0; i < m_pixel_size.y; i++)
			{
				m_vArray[j + i * m_pixel_size.x].position = { (float)j,(float)i };

				Vector2i babygronk(j,i); 
				
				Vector2f fanum = mapPixelToCoords(babygronk);

				size_t counter = countIterations(fanum);
				Uint8 r, g, b;
				iterationsToRGB(counter, r, g, b);
				m_vArray[j + i * m_pixel_size.x].color = Color(r, g, b);
				
			}
		}
		m_state = State::DISPLAYING;
	}
}
void ComplexPlane::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_vArray);
}

void ComplexPlane::zoomIn()
{
	m_zoomCount++;
	Vector2f skibidi;

	skibidi.x = BASE_WIDTH * pow(BASE_ZOOM,m_zoomCount);
	skibidi.y = BASE_HEIGHT * m_aspectRatio* pow(BASE_ZOOM,m_zoomCount);

	m_plane_size.x = skibidi.x;
	m_plane_size.y = skibidi.y;

	m_state = State::CALCULATING;
}
void ComplexPlane::zoomOut()
{
	m_zoomCount--;
	Vector2f hawkTuah;

	hawkTuah.x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	hawkTuah.y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);

	m_plane_size.x = hawkTuah.x;
	m_plane_size.y = hawkTuah.y;

	m_state = State::CALCULATING;
}
void ComplexPlane::setCenter(Vector2i mousePixel)
{
	m_plane_center = mapPixelToCoords(mousePixel);
	m_state = State::CALCULATING;
}
void ComplexPlane::setMouseLocation(Vector2i mousPixel)
{
	m_mouseLocation = mapPixelToCoords(mousPixel);

}
void ComplexPlane::loadText(Text& text)
{
	stringstream out;

	out << "Mandelbrot Set" << endl;
	out << "Center: " << m_plane_center.x <<" , " << m_plane_center.y << endl;
	out << "Cursor: " << m_mouseLocation.x << " , " << m_mouseLocation.y << endl;
	out << "Left-click to Zoom in" << endl;
	out << "Right-click to Zoom out" << endl;
	text.setString(out.str());
}
size_t ComplexPlane::countIterations(Vector2f coord)
{
	complex <float> c(coord.x, coord.y);
	complex <float> z = c;
	int i = 0;
	while (abs(z) < 2.0 && i < 64)
	{
		z = z * z + c;
		i++;
	}
	return i;
}
void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
	if (count == MAX_ITER)
	{
		r = 0;
		g = 0;
		b = 0;
	}
	if (count < 10)
	{
		r = 255;
		g = 0;
		b = 242;
	}
	else if (count < 15)
	{
		r = 159;
		g = 110;
		b = 226;
	}
	else if (count < 25)
	{
		r = 63;
		g = 157;
		b = 136;
	}
	else if (count < 35)
	{
		r = 32;
		g = 55;
		b = 35;
	}
}
Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
	float hawk = ((mousePixel.x - 0.0f) / (m_pixel_size.x - 0.0f)) * m_plane_size.x + (m_plane_center.x - m_plane_size.x / 2.0f);

	float tuah = ((mousePixel.y - 0.0f) / (m_pixel_size.y - 0.0f)) * m_plane_size.y + (m_plane_center.y - m_plane_size.y / 2.0f);

	return Vector2f(hawk, tuah);

}