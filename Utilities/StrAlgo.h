#ifndef STRALGO_H
#define STRALGO_H
#include <string>
#include <vector>
#include <sstream>
namespace yxp_utility
{
	class StrAlgo
	{
	public:
		/// <summary>
		/// 支持有空格的情况
		/// </summary>
		static std::vector<std::string> split(const std::string& src, char delim);

		/// <summary>
		/// 代码更少，但是不能处理存在空格的情况
		/// </summary>
		static std::vector<std::string> split2(const std::string& src, char delim);

		/// <summary>
		/// 拼接字符串,'\0'表示空字符
		/// </summary>
		static std::string join(const std::vector<std::string>& strs, char delim = '\0');

		/// <summary>
		/// 拼接字符串,'\0'表示空字符
		/// </summary>
		template<typename Pred>
		static std::string joinIf(const std::vector<std::string>& strs, char delim, Pred pred);

		/// <summary>
		/// 判断以appendix结尾
		/// </summary>
		static bool endsWith(const std::string& str, const std::string& appendix);

		/// <summary>
		/// 判断以prefix开始
		/// </summary>
		static bool startsWith(const std::string& str, const std::string& prefix);

		/// <summary>
		/// 删除首部prefix
		/// </summary>
		static std::string trimStart(const std::string& str, const std::string& prefix=" ");

		/// <summary>
		/// 删除尾部appendix
		/// </summary>
		static std::string trimEnd(const std::string& str, const std::string& appendix=" ");

		/// <summary>
		/// 删除首部和尾部的del
		/// </summary>
		static std::string trim(const std::string& str, const std::string& del=" ");

		/// <summary>
		/// 替换全部from为to，若未找到，直接返回
		/// </summary>
		static std::string replaceAll(const std::string& str, const std::string& from, const std::string& to);

		/// <summary>
		/// 替换第一个from为to，若未找到，直接返回
		/// </summary>
		static std::string replaceFirst(const std::string& str, const std::string& from, const std::string& to);

		/// <summary>
		/// 替换第一个from为""，若未找到，直接返回
		/// </summary>
		static std::string eraseFirst(const std::string& str, const std::string& from);

		/// <summary>
		/// 替换全部from为""，若未找到，直接返回
		/// </summary>
		static std::string eraseAll(const std::string& str, const std::string& from);

		/// <summary>
		/// 是否回文
		/// </summary>
		static bool isPalindrome(const std::string&str);

	};
}

namespace yxp_utility
{
	std::vector<std::string> StrAlgo::split(const std::string& src, char delim)
	{
		if (src == "")
			return{};

		std::vector<std::string> res;
		std::string tmp = src;

		size_t index = 0;
		size_t last = 0;
		last = tmp.find_first_not_of(delim, last);//找到第一个不为分隔符的字符
		index = tmp.find_first_of(delim, last);//找到第一个分隔符
		if (index == std::string::npos) //没找到
			return{};
		while (index != std::string::npos)//npos代表字符串的结尾
		{
			std::string target = tmp.substr(last, index - last);
			res.push_back(target);

			//last = index +1;
			last = tmp.find_first_not_of(delim, index);
			index = tmp.find_first_of(delim, last);
		}
		if (index == std::string::npos && tmp.length() > last)//到末尾了,如果整个长度大于last坐标,说明还有最后一个字符要放到vector
			res.push_back(tmp.substr(last));
		//#if 1
		//	std::cout << v.size() << std::endl;
		//	for (size_t i = 0; i < v.size(); i++)
		//	{
		//		std::cout << "i=" << i << "," << v[i].c_str() << std::endl;
		//	}
		//#endif
		return res;
	}

	std::vector<std::string> StrAlgo::split2(const std::string& src, char delim)
	{
		std::stringstream sstr(src);
		std::string tmp;
		std::vector<std::string> v;
		while (std::getline(sstr, tmp, ','))
			v.push_back(tmp);
		return v;
	}

	std::string StrAlgo::join(const std::vector<std::string>& strs, char delim)
	{
		/*if (strs.empty())
			return "";
		string res = "";
		for (size_t i = 0; i < strs.size(); ++i)
		{
			res += strs[i];
			if (i != strs.size() - 1 && delim != '\0')
				res += delim;
		}
		return res;*/
		return joinIf(strs, delim, [](const std::string &val) { return true; });
	}

	template<typename Pred>
	static std::string StrAlgo::joinIf(const std::vector<std::string>& strs, char delim, Pred pred)
	{
		if (strs.empty())
			return "";
		std::string res = "";
		for (size_t i = 0; i < strs.size(); ++i)
		{
			if (pred(strs[i]))
			{
				res += strs[i];
				if (i != strs.size() - 1 && delim != '\0')
					res += delim;
			}
		}
		if (delim != '\0')
			res = trimEnd(res, std::string(1, delim));
		return res;
	}

	bool StrAlgo::startsWith(const std::string& str, const std::string& prefix)
	{
		if (prefix == "")
			throw std::runtime_error("prefix is empty!!!");

		if (str == "" ||
			str.length() < prefix.length() ||
			str.substr(0, prefix.length()) != prefix)
			return false;

		return true;
	}

	bool StrAlgo::endsWith(const std::string& str, const std::string& appendix)
	{
		if (appendix == "")
			throw std::runtime_error("appendix is empty!!!");

		if (str == "" ||
			str.length() < appendix.length() ||
			str.substr(str.length() - appendix.length()) != appendix)
			return false;

		return true;
	}

	std::string StrAlgo::trimStart(const std::string& str, const std::string& prefix)
	{
		if (!startsWith(str, prefix))
			return str;
		std::string res = str;
		while (startsWith(res, prefix))
			res = res.substr(prefix.length());
		return res;
	}

	std::string StrAlgo::trimEnd(const std::string& str, const std::string& appendix)
	{
		if (!endsWith(str, appendix))
			return str;
		std::string res = str;
		while (endsWith(res, appendix))
			res = res.substr(0, res.length() - appendix.length());
		return res;
	}

	std::string StrAlgo::trim(const std::string& str, const std::string& del)
	{
		std::string res = str;
		if (endsWith(str, del))
			 res = trimEnd(res,del);
		
		if (startsWith(str, del))
			 res = trimStart(res, del);
		return res;
	}

	std::string StrAlgo::replaceAll(const std::string& str, const std::string& from, const std::string& to)
	{
		if (str.find(from) == std::string::npos)
			return str;
		std::string res = str;
		std::string::size_type pos = res.find(from);
		do
		{
			res = res.replace(pos, from.length(), to);
			pos = res.find(from, pos);
		}
		while (pos != std::string::npos);
		return res;
	}

	std::string StrAlgo::replaceFirst(const std::string& str, const std::string& from, const std::string& to)
	{
		if (str.find(from) == std::string::npos)
			return str;
		std::string res = str;
		std::string::size_type pos = res.find(from);
		res = res.replace(pos, from.length(), to);
		return res;
	}

	std::string StrAlgo::eraseFirst(const std::string& str, const std::string& from)
	{
		return replaceFirst(str,from,"");
	}

	std::string StrAlgo::eraseAll(const std::string& str, const std::string& from)
	{
		return replaceAll(str, from, "");
	}
	
	bool isPalindrome(const std::string& str)
	{
		for (int i = 0, j = str.length() - 1; i < j; i++, j--)
			if (str[i] != str[j])
				return false;
		return true;
	}
}
#endif