#include "EngineString.h"
#include <Windows.h>
#include "EngineDebug.h"

UEngineString::UEngineString() 
{
}

UEngineString::~UEngineString() 
{
}

std::wstring UEngineString::AnsiToUniCode(std::string_view _View)
{
	// 윈도우 지원합니다.
	// 국가코드와 컴파일시의 문자열의 배합을 알고 있는것은 window이기 때문
	// 변환함수가 있다면 window가 지원해 줘야 합니다.
	// MultiByteToWideChar는 멀티바이트를 유니코드로 변경할수 있다.
	// 이함수의 역할이 2가지가 있습니다.
	// 첫번째 
	// 문자열을 변환하면 크기가 변경됩니다.

	// 1바이트이거나 2바이트인 문자열 => 멀티바이트
	// 무조건 2바이트 하는 => 유니코드
	// 바이트 사이즈가 바뀔겁니다.

	// char Arr[5000] => 멀티바이트 문자열
	// wchar_t wArr[] => 그걸 변환한걸 받을 wide바이트 배열 ??????????
	// 일반적으로 얼마나 필요한데? 
	// 이 함수는 2가지 역할이 있다.
	// 변환할 문자열만 넣어줬을때는
	// 변환되어지는 크기를 리턴합니다.
	// int Size = 필요한 wchar_배열의 크기를 리턴합니다.

	//UINT CodePage, = CP_ACP 현재 window에 설정된 초기 문자열 인코딩으로 처리해달라
	//DWORD dwFlags, = 변환할때 추가 정보가 있나요? 아니요 0 => 디폴트 너의 플래그애서 알고 싶지 않아 0=> 디폴트로 해줘
	//LPCCH lpMultiByteStr, = 변환할 문자열
	//int cbMultiByte, => 변환할 문자열의 길이
	//LPWSTR lpWideCharStr, => wide 바이트 문자열 => 변환을 받을 nullptr 넣어주면 이녀석은 크기를 리턴한다
	//int cchWideChar => wide 바이트 문자열의 크기
	int Size = MultiByteToWideChar(CP_ACP, 0, _View.data(), static_cast<int>(_View.size()), nullptr, 0);

	if (0 == Size)
	{
		MsgBoxAssert("문자열 변환에 실패했거나 크기가 0인 문자열을 넣어줬습니다");
		return L"";
	}

	// std::string이나 std::wstring 내부에 std::vector<char>
	// std::vector<char> Vector;
	// Vector[0] => char&
	// &Vector[0] => *char

	//wchar_t* Arr = new wchar_t[Size];
	//delete Arr;
	std::wstring Result;
	Result.resize(Size);

	// 변환되어진 개수가 나오는데.
	Size = MultiByteToWideChar(CP_ACP, 0, _View.data(), static_cast<int>(_View.size()), &Result[0], Size);

	if (0 == Size)
	{
		MsgBoxAssert("문자열 변환에 실패했거나 크기가 0인 문자열을 넣어줬습니다");
		return L"";
	}

	// 자연스럽게 RValue 레퍼런스가 되니까 추가 생성은 이루어지지 않겠죠.
	return Result;
}


std::string UEngineString::UnicodeToAnsi(const std::wstring_view& _Text)
{
	// CP_ACP 운영체제가 사용하는거니
// 아무것도 넣지 않으면 => _Text.c_str()이 몇바이트가 되어야 widechar로 변환할수 있는지를 리턴해줍니다.
	int Size = WideCharToMultiByte(CP_ACP, 0, _Text.data(), static_cast<int>(_Text.size()), nullptr, 0, nullptr, 0);

	if (0 == Size)
	{
		return "";
	}

	// _Text 10
	// Size 30

	std::string Result;
	Result.resize(Size);


	Size = WideCharToMultiByte(CP_ACP, 0, _Text.data(), static_cast<int>(_Text.size()), &Result[0], Size, nullptr, nullptr);

	if (0 == Size)
	{
		return "";
	}

	return Result;
}

std::string UEngineString::UnicodeToUTF8(const std::wstring_view& _Text)
{
	// CP_ACP 운영체제가 사용하는거니
// 아무것도 넣지 않으면 => _Text.c_str()이 몇바이트가 되어야 widechar로 변환할수 있는지를 리턴해줍니다.
	int Size = WideCharToMultiByte(CP_UTF8, 0, _Text.data(), static_cast<int>(_Text.size()), nullptr, 0, nullptr, 0);

	if (0 == Size)
	{
		MsgBoxAssert("문자열을 변환할수가 없습니다.");
		return "";
	}

	// _Text 10
	// Size 30

	std::string Result;
	Result.resize(Size);


	Size = WideCharToMultiByte(CP_UTF8, 0, _Text.data(), static_cast<int>(_Text.size()), &Result[0], Size, nullptr, nullptr);

	if (0 == Size)
	{
		MsgBoxAssert("문자열을 변환에 실패했습니다.");
		return "";
	}

	return Result;
}

std::string UEngineString::AnsiToUTF8(std::string_view _Text)
{
	std::wstring UniCode = AnsiToUniCode(_Text);
	return UnicodeToUTF8(UniCode);
}


std::wstring UEngineString::UTF8ToUnicode(const std::string_view& _Text)
{
	std::wstring UniCode;

	int32_t Len = MultiByteToWideChar(
		CP_UTF8,
		0,
		_Text.data(),
		static_cast<int32_t>(_Text.size()),
		nullptr, // 이부분을 nullptr로 넣어주면 변환 함수로 동작하는게 아니고. 변환길이를 체크하는 함수로 동작한다.
		0
	);

	if (0 >= Len)
	{
		// UEngineString::GetWindowLastErrorPrint();
		return L"";
	}

	UniCode.resize(Len);

	Len = MultiByteToWideChar(
		CP_UTF8,
		0,
		_Text.data(),
		static_cast<int32_t>(_Text.size()),
		&UniCode[0],
		Len
	);

	if (0 >= Len)
	{
		// UEngineString::GetWindowLastErrorPrint();
		return L"";
	}

	return UniCode;
}

std::string UEngineString::UTF8ToAnsi(std::string_view _Text)
{
	std::wstring UniCode = UTF8ToUnicode(_Text);
	std::string Return = UnicodeToAnsi(UniCode);
	return Return;
}

std::string UEngineString::ToUpper(std::string_view View)
{
	std::string Name = View.data();

	for (char& _Ch : Name)
	{
		_Ch = std::toupper(_Ch);
	}

	return Name;
}