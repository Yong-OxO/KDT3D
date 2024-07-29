// 솔루션 탐색기 -> 모든 파일 표시로 변경

// 프로젝트 우클릭 -> 속성 -> 중간 디렉터리, 출력 디렉터리 변경
// 프로젝트 우클릭 -> 속성 -> C++20

// 솔루션(sln) 파일, 프로젝트(vcxproj) 파일 notepad로 열어서 봤다.
// - 프로젝트: xml이라는 문법으로 만들어져 있다.

// 빌드(Build)
// 실행 파일을 만드는 과정
// - 전처리(Preprocess): 소스코드에 담긴 메타 정보를 처리한다
// - 컴파일(Compile): 소스코드를 머신이 읽을 수 있는 파일로 변환한다
//                     (기계어 (바이너리(0,1))로 변환, 기계어를 사람이 읽을 수 있게 변환한게 어셈블리어)
// - 링크(Link): 컴파일 단계에서 변환된 여러 Object파일을 exe로 합친다
//               (우리가 작성한 소스코드 + 가져다 쓴 코드(라이브러리) 등을 합친다)

// *.pdb
// - 디버깅을 위한 기호 정보가 들어있다.
// - 실제로 유저에게 배포할때는 포함되면 안된다.

// 컴파일러
// - 컴파일러 제조사가 컴파일러를 표준 C++문법을 따라서 컴파일 되게 구현한 프로그램
//  - MSVC(MicroSoft Visual C, C++) Compiler
//  - gcc


// include 전처리 지시자
// (전처리 지시자는 컴파일러에게 알려주는 기능)
// include 뒤에 나오는 파일을 포함하겠다
// 포함이란 #include 부분에 대상 파일을 복사 붙혀넣기 한다

// Input Output Stream
#include <iostream>
#include <format>

int GInt = 0;

int main()
{
    // 브레이크 포인트(Break point): F5로 프로그램을 실행(디버거를 붙혀서 실행)
    // 을 하면 Break point를 만날 때 까찌 실행된다.
    // 브레이크 포인트 생성 방법
    //  - 원하는 라인 왼쪽에 마우스를 올리면 흰색 원이 생기는데, 이를 클릭
    //  - 원하는 라인에 캣럿(클릭하면 생기는 깜박이는 수직선)을 두고 F9를 눌러서 켰다 껐다

    // F10: 처음에 프로그램을 디버거를 붙혀서 켜고 첫 시작점부터 멈춰 있는다
    //      이후 F10으로 한줄씩 실행이 가능하다
    // F5: 디버거를 붙혀서 프로그램을 실행하고 Break point를 만날 때 까지 쭉 실행

    // 디버거가 활성화된 상태에서 && BreakPoint 등으로 멈춰 있는 상태에서
    // 우클릭 -> 디스어셈블리로 이동을 클릭하시면 어셈블리 코드를 확인 하실 수 있습니다.

#pragma region 01. 표준 입출력 (cout, cin)
    //{
    //    // 변수
    //    // 변수타입 변수이름 = 초기값
    //    int a = 10;
    //    int b{ 0 };
    //    std::cout << "숫자를 입력해주세요: ";
    //    std::cin >> a;

    //    // std라는 namespace(카테고리)에 있는 cout 함수를 호출
    //    std::cout << "안녕하세요" << std::endl;
    //    std::cout << "안녕하세요 " << a << " " << 20 << std::endl;
    //}
    
    // Ctrl+K -> (Ctrl누르고 있는 상태에서 K키는 때고) C: 선택한 라인 주석
    // Ctrl+K -> (Ctrl누르고 있는 상태에서 K키는 때고) U: 선택한 라인 주석 제거
    //int a = 20;
    //std::cout << "안녕하세요 " << a << " " << 20 << std::endl;
#pragma endregion

#pragma region 02. 리터럴(literal)
    {
        // 리터럴은 코드에 표시한 숫나 문자열과 같은 값 을 의미
        // 십진수
        int V{ 100 };
        // 8진수 : 0144
        int V2{ 0144 }; // 쓸일 없다
        // 16진수 : 0x64
        int V3{ 0x64 };
        // 2진수 : 0b01100100 // 쓸일 없다
        int V4{ 0b01100100 };

        // 부동소수점(floating point): 3.14f
        float F{ 3.14f };

        // 배정도 부동소수점(double): 3.14
        double D{ 3.14 };

        // 단일 문자
        char C{ 'a' }; // ASCII 코드 표에 따라 숫자가 저장됨
        // 문자열 "Hello"

        char CC = 100;
    }
#pragma endregion

#pragma region 03. 변수(Variable)*
    {
        // 1Byte == 8bit (표현 가능한 범위 0~255)
        // 2진수로 나타내는 경우
        // 0000 0000 ~ 1111 1111
        //                     2^0 = 1
        //                    2^1  = 2
        //                   2^2   = 4
        //                  2^3    = 8
        //                2^4      = 16
        //               2^5       = 32
        //              2^6        = 64
        //             2^7         = 128
        // 10진수로 나타내는 경우 (위 값을 모두 더하면됨)
        // 0~255
        // 1024Byte == 1KB
        // 1024KB   == 1MB
        // 1024MB   == 1GB
        // 1024GB   == 1TB

        // 1000KiB  == 1MiB
        // 1000MiB  == 1GiB

        // 자료형: 타입 크기는 Byte에 해당
        // 정수형: char(1Byte), short(2Byte), int(4Byte), long(4Byte), long long(8Byte), __int64(8Byte)
        //         주로 사용: char, int
        // 실수형: float(4Byte), double(8Byte)
        {
            int Var{ 0 }; // 초기화 연산자로 변수를 선언과 동시에 초기화한다.
            Var = 10; // 대입 연산자를 사용해서 값을 변경
        }
        {
            // 4Byte 정수형 signed 타입
            // signed타입: 음수를 표현할 수 있다
            signed int Var{ -1 };
            Var = Var + 1;

            // unsigned를 붙히면 부호가 없는 타입
            unsigned int Var2{ (unsigned int)-1};
            Var2 = Var2 + 1;

            unsigned int Var3{ 4294967295 };
            Var3 = Var3 + 1;

            unsigned char C = 254;
            C = C + 1;
            C = C + 1000;
        }
        {
            // 2Byte 정수형
            // -32,768 ~ 32,767
            short S1{ 32767 };
            S1 = S1 + 1;    // -32,768
            S1 = S1 - 1;    // +32,767

            signed short S2{ 20 };
            unsigned short S3 = 30;
        }
        {
            // 4Byte 정수형
            long L1{ 14L };
        }
        {
            // 8Byte 정수형
            long long LL1{ 14LL };
            unsigned int Var3{ 4294967295 };
            unsigned int Var4{ (unsigned int)4294967296 };
            long long LL2{ 4294967296 };
            //long long LL3{ (unsigned int)4294967296 };
        }
        {
            // 4Byte 실수형
            // 단정도(single) 부동소수점
            // 부동소수점은 컴퓨터에서 부동소수점을 표현하는
            // 특징으로 인해서 오차가 발생할 수 있다.
            float F{ 3.14F };
            int Int{ (int)3.14F };

            // Debug 인 경우 메모리 뒷쪽에
            // 추가 정보가 기본적으로 들어가 있어서
            // 이를 비활성화 하면 변수 크기만큼만 딱 공간을 확보한다
            // 프로젝트 속성 -> C/C++ -> 코드 생성 -> 기본 런타임 검사 -> 기본값
        }
        {
            // 8Byte 실수형
            double D{ 3.14 };
        }
        {
            // 1Byte 정수형
            unsigned char C = 255;
            char C2 = (char)255;
            unsigned char C3 = 'A'; // ASCII 코드 표에 대응되는 수치로 변환해서 저장

            int Int = 'A';
            int Int2 = 65;
        }
        // 유니코드 (다국어 처리가 가능, char는 단일 char로는 불가능)
        {
            // 2Byte
            wchar_t W{ L'A' };
            wchar_t W2{ L'가' };
            wchar_t W3{ L'早' };
            //char C{L'가'}; // 표기 불가
        }
        // 부울타입(boolean) 참과 거짓
        {
            // 1Byte
            bool B0 = true; // 1
            bool B1 = false; // 0
            bool B2 = 0; // false
            bool B3 = 1; // true;
            bool B4 = 22; // true;
        }
        // 부동소수점 오차
        {
            double Value = 0.0;
            if (Value == 0.0)
            {
                std::cout << "Value가 0입니다.\n";
            }
            Value = Value + 0.1;
            Value = Value + 0.1;
            Value = Value + 0.1;

            if (Value == 0.3)
            {
                std::cout << "Value가 0.3입니다.\n";
            }
        }

        // 초기화(initailization)
        {
            int IntNoInit;  // 초기화를 하지 않은 변수
            // 초기화: 변수를 선언함과 동시에 값을 지정하는 것
            IntNoInit = 10; // 초기화가 아니라, 값을 대입

            int IntZeroInit = 0; // 선언과 동시에 값을 지정(초기화)
            int IntZeroInit2{ 0 };
            int IntZeroInit3{ };    // 자동으로 0으로 초기화
            float Float{};  // 0으로 초기화
        }
        // 형변환(Cast): 서로 다른 타입으로 변환
        // C++에는 타입(int, float, ...)있기 때문에 타입간 변환이
        // 필요한 상황이 발생합니다.
        {
            float Float{ 3.14f };
            int Int = Float;    // 묵시적 casting "경고"
            int Int2 = (int)Float; // 명시적 casting, C스타일 cast
            int Int3 = int(Float);  // 명시적 casting, C스타일
            int Int4 = static_cast<int>(Float); // C++ 버전의 명시적 Cast

            // 2Byte 정수
            short Short{ 10 };
            // 4Btye 정수
            int Int5 = Short; // 묵시적 casting
            // int(4Byte)가 short(2Byte)보다 더 크고,
            // 둘다 정수 타입이기 때문에 경고가 발생하지 않습니다.

            /*int Int6 = 999999;
            short Short1 = Int6;*/ // 값이 잘림!, 경고도 발생하지 않는데 주의해서 사용 해야 겠습니다.
        }
    }
#pragma endregion

#pragma region 04. 지역변수, 전역변수와 메모리
    {
        // 지역변수는 지금까지 사용한 바와 같이 스코프({})의 시작과 끝 내부에서 선언되는
        // 변수를 의미합니다.

        // 전역변수는 함수 밖에서 선언된 변수를 의미합니다.
        // 선언된 전역변수는 선언 이후에서는 스코프 내부에서 접근 가능
        GInt = 500;

        // 유저 영역의 메모리 공간은 크게 4구획을 나누어 져있다고 생각하시면 편합니다.
        // [코드 영역]   : 소스코드가 기계어로 변환되어 실제 로직을 수행하는 코드 정보
        // [데이터 영역] : 전역변수, static변수 등
        // [Heap]        : 동적 할당 (아직 배우지 않음)
        // [Stack]       : 지역 변수


        // [프로그램의 메모리 구조]
        // ---------------- 소스 코드 영역 -------------
        // ... 여러분 또는 누군가가 작성해둔 코드가 어셈으로 기록되어 있다
        // -----------------데이터 영역 ----------------
        // ... 전역변수, static(정적) 변수
        // ----------------- Heap 영역 -----------------
        // ... 동적 할당 (실행 중에 메모리 요청을 하는 것)
        // ..
        // ..
        // 
        // 
        // 
        // 
        // (RBP + 상대주소(0)) [a] (4byte)
        // (RBP + 상대주소(1)) [b] (4byte)
        // (RBP + 상대주소(2)) [c] (4byte)
        // (RBP + 상대주소(3)) [d] (4byte)
        // (RBP + 상대주소(4)) [e] (4byte)
        // (함수의 변수목록의 시작주소인 RBP 기준으로 + 상대 주소)
        // ....
        // --------------- Stack 영역 ------------------
        
        /*
        [Code 영역]
        {
            (0x00007FF7AF454FB3) Main함수 기준점으로 부터 Stack의 시작 지점으로 부터 일정 위치가 떨어진 곳에 1을 넣어라
        }

        [Stack 영역]
        {
            - Main의 stack 시작 위치
            - (0x00000003FA99F7A8)a = 10
            - b = ...
        }
        */
        int a, b, c, d, e, f, g, h, i, j, k;

        a = 10;
        b = 20;
        c = 30;
        d = 40;
        e = 50;
    }
#pragma endregion

#pragma region 05. 연산자들
    {
        // 단항(unary; 유너리) 연산자: 표현식(expression) 하나를 계산
        // 이항(binary; 바이너리) 연산자: 표현식 2개를 계산
        // 삼항(temary; 텀메리) 연산자: 표현식 3개를 계산

        // 대입 연산자[이항]: 오른쪽 값을 왼쪽의 표현식에 대입하는 연산자
        {
            int i;
            i = 0;
            int k;
            k = i;
        }
        // [단항] 표현식의 참 / 거짓 (참: 보통1, 0이 아닌 값 / 거짓: 0)
        {
            bool b1{ true };    // 참
            bool b2{ 1 };       // 참
            bool b3{ false };   // 거짓
            bool b4{ 0 };       // 거짓

            bool b5{ !true };   // 참이 아니다(부정, not) == 거짓(false)
            bool b6{ !false };  // 거짓이 아니다 == 참(true)
            
            bool b7{ true };    // 참
            bool b8{ !b7 };     // b7이 참인데 b7(참)이 아니다 == 거짓(false)
        }
        // [이항]사칙 연산
        {
            int a{ 1 + 2 }; // 1 + 2 = 3
            int b{ a + 3 }; // a + 3 = 3 + 3 = 6

            int c{ 1 - 2 }; // 1 - 2 = -1
            unsigned int c2{ unsigned int(1 - 2) }; // 1 - 2 = -1 -> unsigned int 엄청 큰 값

            int d{ c * 3 }; // -1 * 3 = -3

            int e{ 10 / 3 }; // 3
            float f{ 10 / 3 }; // int(10) / int(3) = int(3) -> float f = 3
            float f2{ 10.f / 3.f };
        }
        // [이항] mod, 나머지 연산자
        {
            int m{ 10 % 3 };    // 몫 3, 나머지 1
            int m2{ 5 % 2 };    // 몫 2, 나머지 1
            int m3{ 6 % 2 };    // 몫 3, 나머지 0
        }
        // [단항]후행 / 선행 연산자
        {
            // 후행 증가
            {
                int i{ 0 };
                // i++;
                int k = i++;    // k: 0, i: 1

                // 식 내부에 후행 연산자를 쓰지 마라
                // 실수할 여지가 많다
            }
            // 선행 증가
            {
                int i{ 0 };
                //++i;
                int k = ++i;    // k: 1, i: 1
            }
            // 후행 감소
            {
                int i{ 0 };
                //i--;
                int k{ i-- }; // k: 0, i: -1
            }
            // 선행 감소
            {
                int i{ 0 };
                //--i;
                int k{ --i }; // k: -1, i: -1
            }
        }
        
        // 사칙연산 축약 표현
        {
            int i{ 1 };
            int k{ 2 };

            //i = i + k; // 1 + 2 -> 3
            i += k; // 1 + 2 -> 3
            i += 2; // 3 + 2 -> 5

            i -= 2; // 5 - 2 = 3

            i *= 2; // 3 * 2 = 6
            i /= 2; // 6 / 2 = 3
            i %= 2; // 3 % 2 = 몫 1 나머지 1 <<
        }

        // 비트 단위 연산
        {
            // AND 연산
            {
                // 둘다 1이면 결과가 1
                // 하나라도 0이면 결과가 0
                // 
                // 0010 = 2
                // 1111 = 2^3 + 2^2 + 2^1 + 2^0 = 8 + 4 + 2 + 1 = 15
                // --------- AND
                // 0010 = 2
                char c1 = 0b0010;
                char c2 = 0b1111;
                char c3 = c1 & c2; // 2
            }
            // OR 연산
            {
                // 둘중에 하나라도 1이면 결과가 1
                // 둘다 0이면 결과가 0
                //
                // 0010         // 2
                // 1110         // 14
                // --------- OR
                // 1110         // 14
                char c1 = 0b0010;
                char c2 = 0b1110;
                char c3 = c1 | c2; // 14
            }
            // XOR 연산 (exclusive or)
            {
                // 서로 다르면 결과가 1
                // 서로 같으면 결과가 0
                //
                // 0010
                // 1111
                // -------- XOR
                // 1101         // 2^3 + 2^2 + 2^0 = 13

                char c1 = 0b0010;
                char c2 = 0b1111;
                char c3 = c1 ^ c2; // 13

                // 1101
                // 0010
                // -------- XOR
                // 1111
                c3 = c3 ^ c1;
                c3 = c3 ^ c1;
                c3 = c3 ^ c1;
                c3 = c3 ^ c1;
                c3 = c3 ^ c1;
            }

            // 비트 이동(shift) 연산
            {
                // 왼쪽으로 비트 이동
                {
                    // 0000 0001
                    // 왼쪽으로 한칸 이동
                    // 0000 0010
                    unsigned char C0 = 5;       // 0000 0101 : 5
                    unsigned char C1 = C0 << 1; // 0000 1010 : 8 + 2 = 10
                    unsigned char C2 = C0 << 2; // 0001 0100 : 20
                    unsigned char C3 = C0 << 3; // 0010 1000 : 40
                    unsigned char C4 = C0 << 4; // 0101 0000 : 80
                    unsigned char C5 = C0 << 5; // 1010 0000 : 160
                    unsigned char C6 = C0 << 6; // 0100 0000 : 64
                    unsigned char C7 = C0 << 7; // 1000 0000 : 128
                    unsigned char C8 = C0 << 8; // 0000 0000 : 0
                }
                // 오른쪽으로 비트 이동
                {
                    unsigned char C0 = 80;      // 0101 0000 : 80
                    unsigned char C1 = C0 >> 1; // 0010 1000 : 40
                    unsigned char C2 = C0 >> 2; // 0001 0100 : 20
                    unsigned char C3 = C0 >> 3; // 0000 1010 : 10
                    unsigned char C4 = C0 >> 4; // 0000 0101 : 5
                    unsigned char C5 = C0 >> 5; // 0000 0010 : 2
                    unsigned char C6 = C0 >> 6; // 0000 0001 : 1
                    unsigned char C7 = C0 >> 7; // 0000 0000 : 0
                    unsigned char C8 = C0 >> 8; // 0000 0000 : 0
                }
                // 음수의 경우 비트 이동이 조금 다르게 동작
                {
                    // MSB(Most Significant Bit) '1'111 1111
                    char C0 = -1;       // 1111 1111 : -1
                    {
                        char C1 = C0 >> 1;  // 1111 1111 : -1
                    }
                    {
                        char C1 = C0 << 1;  // 1111 1110 : -2
                        char C2 = C0 << 2;  // 1111 1100 : -4
                        char C7 = C0 << 7;  // 1000 0000 : -128
                        char C8 = C0 << 8;  // 0000 0000 : 0
                    }
                }
            }
        }

        // 삼항 연산자(temary operator) / 조건 연산자
        {
            int i = 0;

            //      (조건문) ? 참일때 : 거짓일때
            // 조건을 만족하면 : 기준으로 왼쪽 결과
            // 조건을 만족하지 않으면 : 기준으로 오른족 결과
            int k1 = (i == 0) ? 10 : -10;
            int k2 = (i != 0) ? 10 : -10;
        }

        // 연산자 우선순위
        {
            int i1 = 10 - 5 * 5; // 10 - 25 = -15
            int i2 = (10 - 5) * 5; // 5 * 5 = 25
        }
    }
#pragma endregion
#pragma region 06. 열거형(enum; enumerated type; 이넘)*
    {
        {
            const int Iron = 0;
            const int Bronze = 1;
            const int Silver = 2;
            const int Gold = 3;

            int MyTier = Gold;
            if (MyTier == Gold)
            {
                std::cout << "골드 티어 입니다.\n";
            }
        }
        {
            enum class ETier : unsigned char
            {
                Iron,
                Bronze /*= 10*/,
                Silver,
                Gold,
            };

            unsigned char MyTier = (unsigned char)ETier::Gold;
            ETier MyTier2 = ETier::Silver;
            ETier MyTier3 = (ETier)3; // ETier::Gold
            if (MyTier2 == ETier::Silver)
            {
                std::cout << "실버 티어 입니다.\n";
            }
            if (MyTier2 == ETier::Gold)
            {
                std::cout << "골드 티어 입니다.\n";
            }
        }
    }
#pragma endregion
#pragma region 07. 구조체(struct)***
    {
        enum class ETier : unsigned char
        {
            None, 
            Iron,
            Bronze,
            Silver,
            Gold,
        };

        int HP = 10;
        int MP = 20;
        ETier Tier = ETier::None;
        //HP = 20;

        struct FPlayer
        {
            int HP = 10;
            int MP = 20;
            ETier Tier = ETier::None;
            // 3Byte padding
        };

        // FPlayer: 구조체 타입 (구조체: 데이터를 묶어둠)
        // Player: 인스턴스(instance; 실체화된 사례) (메모리에 만들어진 것)
        FPlayer Player{ .MP = 100, .Tier = ETier::Gold };
        FPlayer Player2;
        Player2.HP = 200;
        Player2.MP = 300;
        Player2.Tier = ETier::Iron;

        std::cout << "[Player Info]\n";
        std::cout << std::format("HP: {}, MP: {}, Tier: {}\n", Player2.HP, Player2.MP, (int)Player2.Tier);
        std::cout << "HP: " << Player2.HP << ", MP: " << Player2.MP << ", Tier: " <<   (_int8)Player2.Tier << std::endl;
        // 1바이트가 들어오게 된다면 문자취급이 된다. -> 해당 값의 대응하는 문자가 구현되어있지 않다면 공백이 출력
        // 따라서 Tier 형변환을 했을 경우 1바이트로 하게 된다면 Tier에 해당하는 문자로 치환되지만 구현되어있지 않아 공백이 출력된다.

        

#pragma pack(push, 1) // 가장 큰 자료형의 크기를 1단위로 바꾼다. ex) int는 4칸을 4행에 나눠 들어간다
        // 메모리 낭비를 방지하기 위해 데이터형을 맞춰야된다.
        // ex) char -> int -> char형이라면 (1,0,0,0) (1,1,1,1) (1,0,0,0) 형태가 되어 낭비가 된다
        // 패딩은 구조체 내에 가장 큰 자료형을 기준으로 발생한다.
        // 
        // 패딩 팩을 사용하면 데이터의 용량측면에서 이득을 볼 수 있지만, 접근의 횟수가 많아질 수 있다. 최악의 경우 수행능력이 2배 저하된다.
        // 네트워크에서 자료를 보낼 때는 용량이 적어야 성능도 올라가므로 기본적으로 패딩을 1단위로 놓는다.

        struct FPadding
        {
            char c;
            int i;
            char c1;
        };

#pragma pack(pop)
    }
#pragma endregion

#pragma region 08. 조건문(if / switch)
    {

    }

#pragma endregion
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
