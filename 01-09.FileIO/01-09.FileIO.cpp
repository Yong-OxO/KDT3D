// 01-09.FileIO.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <format>

#include "ThirdParty/IniParser/inicpp.h"

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

int main()
{
	// 1. 기본 C++ File Input Output
	// 2. ini파일 IO
	// 3. json파일 IO

	// 절대 경로: 특정 드라이브를 기준으로 (C:\...) 시작하는 경로 (D:\Dir\Test.txt)
	// 상대 경로: 특정 기준 폴더로 부터 시작하는 경로 ("Dir\Test.txt", "Dir/Test.txt")
	{
		std::vector<int> TestVec1;
		for (int i = 0; i < 10; ++i)
		{
			TestVec1.push_back(i);
		}

		TestVec1[0] -= 1;
		int a = 0;
	}
	// 1. 기본 C++ File IO(Input Output)
	{
		/*
		* 텍스트 모드
		* - 기본적으로 파일을 텍스트 모드로 열면, 운영 체제에 따라 줄바꿈 문자가 추가된다.
		* - 예를 들면, Windows에서는 엔터(\n)를 텍스트 파일에 치면 \r\n 으로 변환됩니다.
		* - 텍스트 모드에서는 파일의 끝을 나타내는 문자가 있을 때 읽기가 중단될 수 있습니다.
		*
		* 바이너리 모드
		* - 데이터가 변환 없이 그대로 읽고 써집니다.
		* - 줄바꿈 문자나 파일의 끝을 나타내는 문자가 변환되지 않습니다.
		* - 사용 예시) 이미지, 음악파일 등 처리
		*
		*/

		// File Write (Text)
		// output file stream: ofstream
		{
			std::ofstream OutputStream = std::ofstream("Test.txt", std::ios::out);
			if (OutputStream.is_open())
			{
				std::string String = "Hello File! Hello~~~\n";
				const size_t WriteSize = String.size();
				OutputStream.write((const char*)&WriteSize, sizeof(size_t));
				OutputStream.write(String.c_str(), String.size());

				int Int = 65;
				OutputStream.write(reinterpret_cast<char*>(&Int), sizeof(int));
				OutputStream.close(); // 파일 닫기
			}
		}
		// File Read (Text)
		{
			std::ifstream InputStream = std::ifstream("Test.txt", std::ios::in);
			if (InputStream.is_open())
			{
				size_t ReadSize = 0;
				InputStream.read(reinterpret_cast<char*>(&ReadSize), sizeof(size_t));
				std::string String;
				String.resize(ReadSize);
				InputStream.read(String.data(), String.size());
				//InputStream >> String;

				int Int = 0;
				InputStream.read(reinterpret_cast<char*>(&Int), sizeof(int));

				InputStream.close();
			}
		}

		// File Write (Binary)
		{
			std::ofstream OutputStream = std::ofstream("TestBinary.txt", std::ios::out | std::ios::binary);
			if (OutputStream.is_open())
			{
				std::string String = "Hello File! Hello~~~\n";
				const size_t WriteSize = String.size();
				OutputStream.write((const char*)&WriteSize, sizeof(size_t));
				OutputStream.write(String.c_str(), String.size());

				int Int = 65;
				OutputStream.write(reinterpret_cast<char*>(&Int), sizeof(int));
				OutputStream.close(); // 파일 닫기
			}
		}
		// File Read (Binary)
		{
			std::ifstream InputStream = std::ifstream("TestBinary.txt", std::ios::in | std::ios::binary);
			if (InputStream.is_open())
			{
				size_t ReadSize = 0;
				InputStream.read(reinterpret_cast<char*>(&ReadSize), sizeof(size_t));
				std::string String;
				String.resize(ReadSize);
				InputStream.read(String.data(), String.size());
				//InputStream >> String;

				int Int = 0;
				InputStream.read(reinterpret_cast<char*>(&Int), sizeof(int));

				InputStream.close();
			}
		}
	}
#pragma region 2. ini 파일 IO
	{
		ini::IniFile File;

		File["A Section"]["FeildKey1"] = 1;
		File["A Section"]["FeildKey2"] = 2;
		File["B Section"]["FeildKey1"] = 3;
		File["B Section"]["FeildKey2"] = 4;
		File["C Section"]["FeildKey1"] = 5;
		File["C Section"]["FeildKey2"] = 6;
		File["D Section"]["FeildKey1"] = "String";

		File.save("IniFile.ini");
	}
	{
		ini::IniFile File("IniFile.ini");
		ini::IniField& Filed = File["A Section"]["FeildKey1"];

		std::string tempstring = Filed.as<std::string>();
		//std::string tempstring2 = File["D Section"]["FeildKey1"];
	}
#pragma endregion

#pragma region 3. rapidjson파일 IO
	{
		struct FPlayer
		{
		public:
			FPlayer() = default;
			FPlayer(const FPlayer&) = default;
			FPlayer(std::string InName, int InLevel, int InExp)
				: Name(InName),
				Level(InLevel),
				Exp(InExp)
			{
			}
			~FPlayer() = default;

			void PrintPlayerInfo()
			{
				std::cout << std::format("Name: {}, Level: {}, Exp: {}\n", Name, Level, Exp);
			}

			void Save(rapidjson::Value& InOutValue, rapidjson::Document::AllocatorType& InAllocator)
			{
				if (Name.empty())
				{
					assert(false);
				}

				rapidjson::Value TempString(rapidjson::kStringType);
				TempString.SetString(Name.c_str(), InAllocator);

				InOutValue.AddMember("PlayerName", TempString, InAllocator);
				InOutValue.AddMember("Level", Level, InAllocator);
				InOutValue.AddMember("Exp", Exp, InAllocator);
			}

			void Load(const rapidjson::Value& InValue)
			{
				if (InValue.HasMember("PlayerName"))
				{
					const char* String = InValue["PlayerName"].GetString();
					Name = String;
				}

				if (InValue.HasMember("Level"))
				{
					Level = InValue["Level"].GetInt();
				}
				if (InValue.HasMember("Exp"))
				{
					Exp = InValue["Exp"].GetInt();
				}
			}

		private:
			std::string Name;
			int Level;
			int Exp;
		};

		// Save
		{
			std::vector<FPlayer> Player;

			for (int i = 0; i < 20; ++i)
			{
				std::string TempString = "PlayerName" + std::to_string(i);
				int TempLevel = 10 + i;
				int TempExp = 100 + i;

				Player.push_back(FPlayer(TempString, TempLevel, TempExp));
			}

			rapidjson::Document Doc(rapidjson::kObjectType);
			rapidjson::Value ArrayValue(rapidjson::kArrayType);
			rapidjson::Document::AllocatorType DocAllocator = Doc.GetAllocator();

			for (FPlayer& iter : Player)
			{
				rapidjson::Value TempValue(rapidjson::kObjectType);

				iter.Save(TempValue, DocAllocator);
				ArrayValue.PushBack(TempValue, DocAllocator);
			}

			Doc.AddMember("Player Info", ArrayValue, DocAllocator);

			rapidjson::StringBuffer Buffer;
			rapidjson::Writer<rapidjson::StringBuffer> Writer(Buffer);
			Doc.Accept(Writer);
			std::string Json(Buffer.GetString(), Buffer.GetSize());

			std::ofstream File("Json File");
			File << Json;
		}

		//Load
		{
			std::vector<FPlayer> Player;
			rapidjson::Document Doc(rapidjson::kObjectType);
			std::ifstream File("Json File");
			
			std::string JsonString;
			std::string TempString;
			while (std::getline(File, TempString))
			{
				JsonString += TempString;
			}

			Doc.Parse(JsonString.data());
			bool bHasPlayer = Doc.HasMember("Player Info");

			if (bHasPlayer)
			{
				// 배열이라는 정보를 같이 가지고 오기 때문에 rapidjson:kArrayType선언이 필요 없다
				rapidjson::Value& ArrayValue = Doc["Player Info"];
				if (ArrayValue.IsArray())
				{
					const rapidjson::SizeType Size = ArrayValue.Size();
					for (int i = 0; i < Size; ++i)
					{
						FPlayer TempPlayer;

						// 마찬가지로 kObject타입이라는 정보를 같이 가지고 오기 때문에 별도의 선언이 필요 없다
						rapidjson::Value& TempValue = ArrayValue[i];
						TempPlayer.Load(TempValue);
						Player.push_back(TempPlayer);
					}
				}
			}

			for (FPlayer& iter : Player)
			{
				iter.PrintPlayerInfo();
			}
		}
	}
#pragma endregion


}