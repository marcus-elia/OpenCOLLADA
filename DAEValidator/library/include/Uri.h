#pragma once

#include <ostream>
#include "no_warning_string"

// https://tools.ietf.org/html/rfc3986

namespace opencollada
{
	class Uri
	{
	public:
		Uri() = default;
		Uri(const std::string & uri);
		Uri(const Uri & baseUri, const Uri & uri);

		bool operator == (const Uri & uri) const;
		bool operator != (const Uri & uri) const;
		bool operator < (const Uri & uri) const;

		bool empty() const;
		bool isValid() const;
		const std::string & str() const;
		const std::string & scheme() const;
		const std::string & authority() const;
		const std::string & path() const;
		const std::string & query() const;
		const std::string & fragment() const;

		void setScheme(const std::string & scheme);
		void setFragment(const std::string & fragment);
		void setPathFile(const std::string & filename);

		std::string pathFile() const;
		std::string nativePath() const;

		void clear();
		void set(const std::string & uri);
		void set(const Uri & baseUri, const Uri & uri);

		static Uri FromNativePath(const std::string & path);
		static std::string Decode(const std::string & str);
		static std::string Encode(const std::string & uri);
		static bool Parse(
			const std::string & uri,
			std::string & scheme,
			std::string & authority,
			std::string & path,
			std::string & query,
			std::string & fragment);

	private:
		static std::string MergePaths(const Uri & baseUri, const std::string & ref_path);

		// Rebuild mUri from mScheme, mAuthority, mPath, mQuery and mFragment
		void rebuild_fast();

	private:
		std::string mUri;
		std::string mScheme;
		std::string mAuthority;
		std::string mPath;
		std::string mQuery;
		std::string mFragment;
		bool mValid = false;
	};
}

std::ostream & operator << (std::ostream & o, const opencollada::Uri & uri);