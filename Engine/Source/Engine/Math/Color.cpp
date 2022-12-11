#include "pch.h"
#include "Color.h"

namespace Engine
{
	Color::Color() :
		XMFLOAT4{0.0f, 0.0f, 0.0f, 1.0f} { }

	Color::Color(const float red, const float green, const float blue) :
		XMFLOAT4{red, green, blue, 1.0f} { }

	Color::Color(const float red, const float green, const float blue, const float alpha) :
		XMFLOAT4{red, green, blue, alpha} { }

	Color::Color(const Vector3Float& rgbColor) :
		XMFLOAT4{rgbColor.x, rgbColor.y, rgbColor.z, 1.0f} { }

	Color::Color(const XMFLOAT4& rgbaColor) :
		XMFLOAT4{rgbaColor.x, rgbaColor.y, rgbaColor.z, rgbaColor.w} { }

	Color::~Color() = default;

	float Color::Red() const
	{
		return x;
	}

	void Color::Red(const float red)
	{
		x = red;
	}

	float Color::Green() const
	{
		return y;
	}

	void Color::Green(const float green)
	{
		y = green;
	}

	float Color::Blue() const
	{
		return z;
	}

	void Color::Blue(const float blue)
	{
		z = blue;
	}

	float Color::Alpha() const
	{
		return w;
	}

	void Color::Alpha(const float alpha)
	{
		w = alpha;
	}

	Color Color::Lerp(const Color& c1, const Color& c2, const float t) noexcept
	{
		using namespace DirectX;
		const XMVECTOR tempC1 = XMLoadFloat4(&c1);
		const XMVECTOR tempC2 = XMLoadFloat4(&c2);

		Color result;
		XMStoreFloat4(&result, XMVectorLerp(tempC1, tempC2, t));
		return result;
	}

	Color::operator DirectX::XMVECTOR() const
	{
		return XMLoadFloat4(this);
	}

	Color::operator float*() const
	{
		return (float*)this;
	}

	bool Color::operator==(const Color& c) const
	{
		using namespace DirectX;
		const XMVECTOR c1 = XMLoadFloat4(this);
		const XMVECTOR c2 = XMLoadFloat4(&c);
		return XMColorEqual(c1, c2);
	}

	bool Color::operator!=(const Color& c) const
	{
		using namespace DirectX;
		const XMVECTOR c1 = XMLoadFloat4(this);
		const XMVECTOR c2 = XMLoadFloat4(&c);
		return XMColorNotEqual(c1, c2);
	}

	Color& Color::operator+=(const Color& c)
	{
		using namespace DirectX;
		const XMVECTOR c1 = XMLoadFloat4(this);
		const XMVECTOR c2 = XMLoadFloat4(&c);
		XMStoreFloat4(this, XMVectorAdd(c1, c2));
		return *this;
	}

	Color& Color::operator-=(const Color& c)
	{
		using namespace DirectX;
		const XMVECTOR c1 = XMLoadFloat4(this);
		const XMVECTOR c2 = XMLoadFloat4(&c);
		XMStoreFloat4(this, XMVectorSubtract(c1, c2));
		return *this;
	}

	Color& Color::operator*=(const Color& c)
	{
		using namespace DirectX;
		const XMVECTOR c1 = XMLoadFloat4(this);
		const XMVECTOR c2 = XMLoadFloat4(&c);
		XMStoreFloat4(this, XMVectorMultiply(c1, c2));
		return *this;
	}

	Color& Color::operator*=(const float s)
	{
		using namespace DirectX;
		const XMVECTOR c = XMLoadFloat4(this);
		XMStoreFloat4(this, XMVectorScale(c, s));
		return *this;
	}

	Color& Color::operator/=(const Color& c)
	{
		using namespace DirectX;
		const XMVECTOR c1 = XMLoadFloat4(this);
		const XMVECTOR c2 = XMLoadFloat4(&c);
		XMStoreFloat4(this, XMVectorDivide(c1, c2));
		return *this;
	}

	Color Color::operator-() const
	{
		using namespace DirectX;
		const XMVECTOR c = XMLoadFloat4(this);
		Color result;
		XMStoreFloat4(&result, XMVectorNegate(c));
		return result;
	}

	Color Color::operator+() const
	{
		return *this;
	}

	Color Engine::operator+(const Color& c1, const Color& c2) noexcept
	{
		using namespace DirectX;
		const XMVECTOR tempC1 = XMLoadFloat4(&c1);
		const XMVECTOR tempC2 = XMLoadFloat4(&c2);
		Color result;
		XMStoreFloat4(&result, XMVectorAdd(tempC1, tempC2));
		return result;
	}

	Color Engine::operator-(const Color& c1, const Color& c2) noexcept
	{
		using namespace DirectX;
		const XMVECTOR tempC1 = XMLoadFloat4(&c1);
		const XMVECTOR tempC2 = XMLoadFloat4(&c2);
		Color result;
		XMStoreFloat4(&result, XMVectorSubtract(tempC1, tempC2));
		return result;
	}

	Color Engine::operator*(const Color& c1, const Color& c2) noexcept
	{
		using namespace DirectX;
		const XMVECTOR tempC1 = XMLoadFloat4(&c1);
		const XMVECTOR tempC2 = XMLoadFloat4(&c2);
		Color result;
		XMStoreFloat4(&result, XMVectorMultiply(tempC1, tempC2));
		return result;
	}

	Color Engine::operator*(const Color& c, const float s) noexcept
	{
		using namespace DirectX;
		const XMVECTOR tempColor = XMLoadFloat4(&c);
		Color result;
		XMStoreFloat4(&result, XMVectorScale(tempColor, s));
		return result;
	}

	Color Engine::operator/(const Color& c1, const Color& c2) noexcept
	{
		using namespace DirectX;
		const XMVECTOR tempC1 = XMLoadFloat4(&c1);
		const XMVECTOR tempC2 = XMLoadFloat4(&c2);
		Color result;
		XMStoreFloat4(&result, XMVectorDivide(tempC1, tempC2));
		return result;
	}

	// std::ostream& operator<<(std::ostream& os, const Color& c)
	// {
	// 	os << "{" << c.Red() << ", " << c.Green() << ", " << c.Blue() << ", " << c.Alpha() << "}";
	// 	return os;
	// }
}