#pragma once

namespace Engine
{
	struct Color final : DirectX::XMFLOAT4
	{
		explicit Color();

		explicit Color(float red, float green, float blue);

		explicit Color(float red, float green, float blue, float alpha);

		explicit Color(const Vector3Float& rgbColor);

		explicit Color(const XMFLOAT4& rgbaColor);

		~Color();

		[[nodiscard]]
		float Red() const;

		void Red(float red);

		[[nodiscard]]
		float Green() const;

		void Green(float green);

		[[nodiscard]]
		float Blue() const;

		void Blue(float blue);

		[[nodiscard]]
		float Alpha() const;

		void Alpha(float alpha);

		static Color Lerp(const Color& c1, const Color& c2, float t) noexcept;

		explicit operator DirectX::XMVECTOR() const;

		explicit operator float*() const;

		bool operator ==(const Color& c) const;

		bool operator !=(const Color& c) const;

		Color& operator+=(const Color& c);

		Color& operator-=(const Color& c);

		Color& operator*=(const Color& c);

		Color& operator*=(float s);

		Color& operator/=(const Color& c);

		Color operator+() const;

		Color operator-() const;

		Color(const Color&)            = default;
		Color& operator=(const Color&) = default;
		Color(Color&&)                 = default;
		Color& operator=(Color&&)      = default;

		//friend std::ostream& operator<<(std::ostream& os, const Color& c);
	};

	Color operator+(const Color& c1, const Color& c2) noexcept;
	Color operator-(const Color& c1, const Color& c2) noexcept;
	Color operator*(const Color& c1, const Color& c2) noexcept;
	Color operator*(const Color& c, float s) noexcept;
	Color operator/(const Color& c1, const Color& c2) noexcept;
	//std::ostream& operator<<(std::ostream& os, const Color& c);
}
