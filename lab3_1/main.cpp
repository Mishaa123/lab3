#include "modAlphaCipher.h"
#include "modAlphaCipher.cpp"


SUITE(KeyTest)
{
// Тест конструктора
    TEST(ValidKey)
    {
        CHECK(L"ДБЁГЗЕЙЖ" == modAlphaCipher(L"ДА").encrypt(L"АБВГДЕЁЖ"));
    }
    
    TEST(LongKey)
    {
        CHECK(L"ДБЙЖ" == modAlphaCipher(L"ДАЗДРАВСТУЕТКОРОЛЬ").encrypt(L"АБВГ"));
    }
    
    TEST(LowCaseKey)
    {
        CHECK(L"ДБЁГЗЕЙЖ" == modAlphaCipher(L"да").encrypt(L"АБВГДЕЁЖ"));
    }

    TEST(DigitsInKey) 
    { 
        CHECK_THROW(modAlphaCipher cp(L"да1"), cipher_error); 
    }
    
    TEST(PunctuationInKey) 
    { 
        CHECK_THROW(modAlphaCipher cp(L"да!"), cipher_error); 
    }
    
    TEST(WhitespaceInKey) 
    { 
        CHECK_THROW(modAlphaCipher cp(L"д а"), cipher_error); 
    }
    
    TEST(EmptyKey) 
    { 
        CHECK_THROW(modAlphaCipher cp(L""), cipher_error); 
    }
    
    TEST(WeakKey) 
    { 
        CHECK_THROW(modAlphaCipher cp(L"ААА"), cipher_error); 
    }

// Тест для метода encrypt  
    struct KeyB_fixture
    {
        modAlphaCipher* p;
        KeyB_fixture() { p = new modAlphaCipher(L"ДАБДАБЕСЕС"); }
        ~KeyB_fixture() { delete p; }
    };
                 
    SUITE(EncryptTest)
    {
        TEST_FIXTURE(KeyB_fixture, UpCaseString)
        {
            CHECK(L"ИХБПГСЙЬЕИИРЁЛРЁПЕ" == p->encrypt(L"ЕХАЛГРЕКАЧЕРЕЗРЕКУ"));
        }
        
        TEST_FIXTURE(KeyB_fixture, LowCaseString)
        {
            CHECK(L"ИХБПГСЙЬЕИИРЁЛРЁПЕ" == p->encrypt(L"ехалгрекачерезреку"));
        }
        
        TEST_FIXTURE(KeyB_fixture, StringWithWhitespaceAndPunct)
        {
            CHECK(L"ИХБПГСЙЬЕИИРЁЛРЁПЕ" == p->encrypt(L"ехал, грека! через реку"));
        }
        
        TEST_FIXTURE(KeyB_fixture, StringWithNumbers)
        {
            CHECK(L"ИХБПГСЙЬЕИИРЁЛРЁПЕ" == p->encrypt(L"ехал1 грека2 через3 реку4"));
        }
        
        TEST_FIXTURE(KeyB_fixture, EmptyString)
        {
            CHECK_THROW(p->encrypt(L""), cipher_error);        
        }

        TEST_FIXTURE(KeyB_fixture, NoAlphaString)
        {
            CHECK_THROW(p->encrypt(L"86423215"), cipher_error);
        }

        TEST(MaxShiftKey)
        {
            CHECK(L"ДФЯКВПДЙЯЦДПДЖПДЙТ" == modAlphaCipher(L"Я").encrypt(L"ЕХАЛГРЕКАЧЕРЕЗРЕКУ"));
        }
    }

// Тест для метода decrypt    
    SUITE(DecryptText)
    {
        TEST_FIXTURE(KeyB_fixture, UpCaseString)
        {
            CHECK(L"ЕХАЛГРЕКАЧЕРЕЗРЕКУ" == modAlphaCipher(L"ДАБДАБЕСЕС").decrypt(L"ИХБПГСЙЬЕИИРЁЛРЁПЕ"));
        }
        TEST_FIXTURE(KeyB_fixture, LowCaseString) { CHECK_THROW(p->decrypt(L"ихБПГСЙЬЕИИРЁЛРЁПЕ"), cipher_error); }
    	TEST_FIXTURE(KeyB_fixture, WhitespaceString)
    	{
        	CHECK_THROW(p->decrypt(L"ИХ БПГСЙ ЬЕИИРЁ ЛРЁПЕ"), cipher_error);
    	}
    	TEST_FIXTURE(KeyB_fixture, DigitsString)
    	{
        	CHECK_THROW(p->decrypt(L"ИХБПГСЙЬЕИИРЁЛРЁПЕ123"), cipher_error);
    	}
    	TEST_FIXTURE(KeyB_fixture, PunctString) { CHECK_THROW(p->decrypt(L"ИХБПГСЙЬЕИИРЁЛРЁПЕ!!!"), cipher_error); }

    	TEST_FIXTURE(KeyB_fixture, EmptyString) { CHECK_THROW(p->decrypt(L""), cipher_error); }
    	TEST(MaxShiftKey)
    	{
            CHECK(L"ЕХАЛГРЕКАЧЕРЕЗРЕКУ" == modAlphaCipher(L"Я").decrypt(L"ДФЯКВПДЙЯЦДПДЖПДЙТ"));
        }

    	}
}

int main(int argc, char** argv)
{
    std::locale loc("ru_RU.UTF-8");
    std::locale::global(loc);
    return UnitTest::RunAllTests();
}
