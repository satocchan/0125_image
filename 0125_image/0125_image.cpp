// pattern_image.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <opencv2/opencv.hpp>
#include <iostream>
#include<string>
#include<array>
#include<vector>
#include<ctime>
#include<cstdlib>
#include<random>
#include "putText_Jpn.h"
#include<windows.h>


std::wstring StringToWString(std::string oString)
{
    // SJIS → wstring
    int iBufferSize = MultiByteToWideChar(CP_ACP, 0, oString.c_str(), -1, (wchar_t*)NULL, 0);

    // バッファの取得
    wchar_t* cpUCS2 = new wchar_t[iBufferSize];

    // SJIS → wstring
    MultiByteToWideChar(CP_ACP, 0, oString.c_str(), -1, cpUCS2, iBufferSize);

    // stringの生成
    std::wstring oRet(cpUCS2, cpUCS2 + iBufferSize - 1);

    // バッファの破棄
    delete[] cpUCS2;

    // 変換結果を返す
    return(oRet);
}


cv::Point center_random(const std::string& text, double fontScale, int thickness, cv::Mat& img, int size)
{
    std::srand(time(NULL));
    int a = (rand() % size) - (size / 2);
    std::srand(time(NULL));
    int b = (rand() % size) - (size / 2);

    if (fontScale == 1)
    {
        cv::Point textOrg(900 + a, 560 + b);
        return textOrg;
    }
    else if (fontScale == 2)
    {
        cv::Point textOrg(875 + a, 570 + b);
        return textOrg;
    }
    else if (fontScale == 3)
    {
        cv::Point textOrg(850 + a, 580 + b);
        return textOrg;
    }
    else if (fontScale == 4)
    {
        cv::Point textOrg(825 + a, 590 + b);
        return textOrg;
    }
    else if (fontScale == 5)
    {
        cv::Point textOrg(800 + a, 600 + b);
        return textOrg;
    }
    else if (fontScale == 6)
    {
        cv::Point textOrg(765 + a, 610 + b);
        return textOrg;
    }
    else if (fontScale == 7)
    {
        cv::Point textOrg(730 + a, 620 + b);
        return textOrg;
    }
    else if (fontScale == 8)
    {
        cv::Point textOrg(695 + a, 630 + b);
        return textOrg;
    }
    else if (fontScale == 9)
    {
        cv::Point textOrg(660 + a, 640 + b);
        return textOrg;
    }
    else if (fontScale == 10)
    {
        cv::Point textOrg(625 + a, 650 + b);
        return textOrg;
    }
    else if (fontScale == 11)
    {
        cv::Point textOrg(590 + a, 660 + b);
        return textOrg;
    }
    else if (fontScale == 12)
    {
        cv::Point textOrg(555 + a, 670 + b);
        return textOrg;
    }
    else if (fontScale == 13)
    {
        cv::Point textOrg(520 + a, 680 + b);
        return textOrg;
    }
    else if (fontScale == 14)
    {
        cv::Point textOrg(485 + a, 690 + b);
        return textOrg;
    }
    else if (fontScale == 15)
    {
        cv::Point textOrg(450 + a, 700 + b);
        return textOrg;
    }
    else if (fontScale == 16)
    {
        cv::Point textOrg(415 + a, 710 + b);
        return textOrg;
    }
    else if (fontScale == 17)
    {
        cv::Point textOrg(380 + a, 720 + b);
        return textOrg;
    }
    else if (fontScale == 18)
    {
        cv::Point textOrg(345 + a, 730 + b);
        return textOrg;
    }
    else if (fontScale == 19)
    {
        cv::Point textOrg(310 + a, 740 + b);
        return textOrg;
    }
    else if (fontScale == 20)
    {
        cv::Point textOrg(275 + a, 750 + b);
        return textOrg;
    }


}

class Image
{
private:
    double fontScale;
    int size;
    int thickness;
    std::string image_text;
    int w = 1920;
    int h = 1080;
    cv::Mat text_img_black;
    cv::Mat text_img_white;
    cv::Mat pattern_img;
    cv::Mat dst;

    int back_black = 60;
    int back_white = 150;
    int letter_black = 75;
    int letter_white = 200;

public:
    Image(double fontScale, int size, int thickness, std::string image_text) :
        fontScale(fontScale), size(size), thickness(thickness), image_text(image_text)
    {
        cv::Mat img(h, w, CV_8UC3, cv::Scalar(back_black, back_black, back_black));
        cv::Mat cpy = img.clone();

        for (int y = 0; y < img.rows; y++)
        {
            for (int x = 0; x < img.cols; x++)
            {
                img.at<cv::Vec3b>(y, x)[0] = back_white * ((x / size + y / size) % 2);//B
                img.at<cv::Vec3b>(y, x)[1] = back_white * ((x / size + y / size) % 2);//G
                img.at<cv::Vec3b>(y, x)[2] = back_white * ((x / size + y / size) % 2);//R
                cpy.at<cv::Vec3b>(y, x)[0] = back_white * ((x / size + y / size) % 2);//B
                cpy.at<cv::Vec3b>(y, x)[1] = back_white * ((x / size + y / size) % 2);//G
                cpy.at<cv::Vec3b>(y, x)[2] = back_white * ((x / size + y / size) % 2);//R
            }
        }
        for (int y = 0; y < img.rows; y++)
        {
            for (int x = 0; x < img.cols; x++)
            {
                if (img.at<cv::Vec3b>(y, x)[0] == 0)
                {
                    img.at<cv::Vec3b>(y, x)[0] = back_black;//B
                    img.at<cv::Vec3b>(y, x)[1] = back_black;//G
                    img.at<cv::Vec3b>(y, x)[2] = back_black;//R
                    cpy.at<cv::Vec3b>(y, x)[0] = back_black;//B
                    cpy.at<cv::Vec3b>(y, x)[1] = back_black;//G
                    cpy.at<cv::Vec3b>(y, x)[2] = back_black;//R
                } 
            }
        }

        std::wstring wss = StringToWString(image_text);
        cv::Point textOrg = center_random(image_text, fontScale, thickness, img, size);

        cv::Mat base_black(h, w, CV_8UC3, cv::Scalar(back_black, back_black, back_black));
        cv::Mat base_white(h, w, CV_8UC3, cv::Scalar(back_white, back_white, back_white));

        sc::myCV::putText_Jpn(base_black, wss, textOrg, TEXT("ＭＳ ゴシック"), fontScale, cv::Scalar(letter_black, letter_black, letter_black), thickness);
        sc::myCV::putText_Jpn(base_white, wss, textOrg, TEXT("ＭＳ ゴシック"), fontScale, cv::Scalar(letter_white, letter_white, letter_white), thickness);
        sc::myCV::putText_Jpn(img, wss, textOrg, TEXT("ＭＳ ゴシック"), fontScale, cv::Scalar(255, 255, 255), thickness);

        for (int y = 0; y < img.rows; y++)
        {
            for (int x = 0; x < img.cols; x++)
            {
                if (((img.at<cv::Vec3b>(y, x)[0] == 254) || (img.at<cv::Vec3b>(y, x)[0] == 212) || (img.at<cv::Vec3b>(y, x)[0] == 176) ||
                    (img.at<cv::Vec3b>(y, x)[0] == 115) || (img.at<cv::Vec3b>(y, x)[0] == 179) || (img.at<cv::Vec3b>(y, x)[0] == 230) ||
                    (img.at<cv::Vec3b>(y, x)[0] == 209) || (img.at<cv::Vec3b>(y, x)[0] == 194) || (img.at<cv::Vec3b>(y, x)[0] == 164) ||
                    (img.at<cv::Vec3b>(y, x)[0] == 144) || (img.at<cv::Vec3b>(y, x)[0] == 87)) && (cpy.at<cv::Vec3b>(y, x)[0] == back_black))
                {
                    img.at<cv::Vec3b>(y, x)[0] = letter_black;
                    img.at<cv::Vec3b>(y, x)[1] = letter_black;
                    img.at<cv::Vec3b>(y, x)[2] = letter_black;
                }
                else if (((img.at<cv::Vec3b>(y, x)[0] == 254) || (img.at<cv::Vec3b>(y, x)[0] == 212) || (img.at<cv::Vec3b>(y, x)[0] == 176) ||
                          (img.at<cv::Vec3b>(y, x)[0] == 115) || (img.at<cv::Vec3b>(y, x)[0] == 179) || (img.at<cv::Vec3b>(y, x)[0] == 230) ||
                          (img.at<cv::Vec3b>(y, x)[0] == 209) || (img.at<cv::Vec3b>(y, x)[0] == 194) || (img.at<cv::Vec3b>(y, x)[0] == 164) ||
                          (img.at<cv::Vec3b>(y, x)[0] == 144) || (img.at<cv::Vec3b>(y, x)[0] == 87)) && (cpy.at<cv::Vec3b>(y, x)[0] == back_white))
                {
                    img.at<cv::Vec3b>(y, x)[0] = letter_white;
                    img.at<cv::Vec3b>(y, x)[1] = letter_white;
                    img.at<cv::Vec3b>(y, x)[2] = letter_white;
                }

            }
        }

        dst = img.clone();
        pattern_img = cpy.clone();
        text_img_black = base_black.clone();
        text_img_white = base_white.clone();
    }
    cv::Mat pattern_image_getter()
    {
        return pattern_img;
    }

    cv::Mat black_text_image_getter()
    {
        return text_img_black;
    }

    cv::Mat white_text_image_getter()
    {
        return text_img_white;
    }

    cv::Mat image_getter()
    {
        return dst;
    }

    std::string text_getter()
    {
        return image_text;
    }

    int fontscale_getter()
    {
        return (int)fontScale;
    }
};

int main()
{
    int size1 = 30;
    int size2 = 60;
    int size3 = 90;


    std::array<std::string, 10> text1_black = { "KSY", "SLM", "AZN", "EKA", "SNY",
                                                "RLK", "MIT", "CFN", "RMC", "YNX"};

    std::array<std::string, 10> text2_black = { "AZM", "YRA", "IRX", "ATE", "YMR",
                                                "SED", "BPL", "XPP", "KGP", "MCM"};

    std::array<std::string, 10> text3_black = { "MNB", "XRI", "WBG", "FYM", "SKT",
                                                "XSD", "AMR", "DRM", "XRF", "KHY"};

    std::array<std::string, 10> text4_black = { "KXY", "MPC", "WHB", "AMA", "KDH",
                                                "CBA", "FZK", "YCC", "HYR", "MFZ"};

    std::array<std::string, 10> text5_black = { "SSX", "MSK", "RRT", "ELF", "PCD",
                                                "CWP", "WYK", "RIW", "SIH", "CSE"};

    std::array<std::string, 10> text6_black = { "IKY", "DXM", "NNF", "FTP", "MGT",
                                                "NKN", "DFI", "LZR", "ENB", "MRW"};

    std::array<std::string, 10> text7_black = { "ZNZ", "MWY", "EZC", "BSM", "EMT",
                                                "SGR", "PZL", "GGR", "KGT", "YID"};

    std::array<std::string, 10> text8_black = { "RHP", "NXH", "IZE", "LZB", "ZDI",
                                                "SXR", "GIP", "MPX", "DBD", "YYM"};

    std::array<std::string, 10> text9_black = { "IIT", "HST", "NEF", "ZRI", "SWW",
                                                "AHS", "BYE", "XAD", "DZH", "HBY"};

    std::array<std::string, 10> text10_black = { "HHE", "CRW", "WGA", "BDN", "HYI",
                                                "EMT", "YTN", "APN", "BSK", "HZI" };

    std::array<std::string, 10> text11_black = { "YDG", "APS", "EGP", "FWI", "TRL",
                                                "HBG", "DCA", "FZE", "BTN", "EGF" };

    std::array<std::string, 10> text12_black = { "PEG", "WEW", "LGC", "CNZ", "LFM",
                                                "YNN", "EPN", "EWK", "HXF", "YAK" };

    std::array<std::string, 10> text13_black = { "GBB", "ANL", "NHY", "NKG", "REW",
                                                "ACD", "WFY", "WAN", "PCY", "EHC" };

    std::array<std::string, 10> text14_black = { "IPD", "KNP", "WBA", "SPK", "BFN",
                                                "TFR", "YBY", "SXX", "HIX", "FLF" };

    std::array<std::string, 10> text15_black = { "WKH", "BSP", "GSW", "PNB", "AIF",
                                                "XFT", "WZH", "CCM", "YFI", "DII" };

    std::array<std::string, 10> text16_black = { "XEW", "EDK", "SKE", "MBR", "PZR",
                                                "TXE", "KND", "TRG", "FPK", "PRW" };

    std::array<std::string, 10> text17_black = { "KBX", "PZR", "XMA", "GLG", "XPF",
                                                "CHD", "PYZ", "IDK", "KEX", "HEZ" };

    std::array<std::string, 10> text18_black = { "WMB", "NEY", "DBK", "BFX", "GAL",
                                                "KCS", "NTR", "KBW", "XLY", "SWD" };

    std::array<std::string, 10> text19_black = { "BHE", "IAK", "ZRC", "NPT", "SKX",
                                                "DMI", "BXY", "ZLX", "RAM", "WCZ" };

    std::array<std::string, 10> text20_black = { "KBF", "MKF", "ZGW", "ZWK", "RKW",
                                                "MNH", "WRC", "SML", "LCK", "AWK" };


    std::array<std::array<std::string, 10>, 20> all_text_black = { text1_black, text2_black, text3_black, text4_black, text5_black,
                                                                   text6_black, text7_black, text8_black, text9_black, text10_black,
                                                                   text11_black, text12_black, text13_black, text14_black, text15_black,
                                                                   text16_black, text17_black, text18_black, text19_black, text20_black };

    std::vector<Image> all_image_black;

    int counter_fontsize_black = 1;
    for (size_t i = 0; i < all_text_black.size(); i++)
    {
        for (size_t j = 0; j < all_text_black[i].size(); j++)
        {
            Image image(counter_fontsize_black, size1, 2 * counter_fontsize_black, all_text_black[i][j]);
            all_image_black.push_back(image);
        }
        counter_fontsize_black += 1;
    }



    /*------------------------------------------------------------------------------------------------------------------------------------------------------*/



    std::array<std::string, 10> text1_white = { "CHK", "IIE", "LDX", "DBR", "NIP",
                                                "DIG", "RPL", "MAB", "CTZ", "WDH" };

    std::array<std::string, 10> text2_white = { "ZKS", "BAN", "NMA", "NYE", "HKZ",
                                                "WIK", "CFT", "NIY", "BRC", "ZEF" };

    std::array<std::string, 10> text3_white = { "ARN", "IZK", "DEA", "XFL", "WFE",
                                                "TYN", "YTL", "BXN", "XTM", "FNF" };

    std::array<std::string, 10> text4_white = { "BBS", "LMD", "SCN", "DPD", "RES",
                                                "SGK", "HWA", "HRK", "ZFE", "FEZ" };

    std::array<std::string, 10> text5_white = { "KFA", "ZIB", "AFH", "EPI", "GTW",
                                                "BII", "BZW", "LTH", "MAD", "AMI" };

    std::array<std::string, 10> text6_white = { "EMW", "ZTE", "LXM", "ASD", "NWP",
                                                "INE", "DMN", "HFA", "ABT", "RSI" };

    std::array<std::string, 10> text7_white = { "EZM", "KPP", "AWF", "BFG", "YWH",
                                                "BLD", "ANL", "BCB", "SHT", "CAH" };

    std::array<std::string, 10> text8_white = { "MKW", "LIW", "GDD", "IEY", "IHX",
                                                "BNN", "YIP", "MYC", "IAG", "LRH" };

    std::array<std::string, 10> text9_white = { "HHS", "KDD", "HSE", "SIA", "EFI",
                                                "WWN", "SEM", "YYB", "SDG", "PSI" };

    std::array<std::string, 10> text10_white = { "FDR", "WSM", "RZM", "NK", "GNK",
                                                "RGN", "SRM", "ZDF", "SYS", "KFD" };

    std::array<std::string, 10> text11_white = { "MIE", "DFZ", "RYM", "CME", "MSR",
                                                "XIA", "IBP", "YYS", "BNP", "SAT" };

    std::array<std::string, 10> text12_white = { "IET", "NFL", "DXW", "DGW", "PNI",
                                                "PMD", "FTK", "YCK", "ZIT", "XIG" };

    std::array<std::string, 10> text13_white = { "ITL", "DFP", "MIL", "HLT", "BCG",
                                                "HPS", "MXM", "ZRM", "IMW", "BHE" };

    std::array<std::string, 10> text14_white = { "HXL", "ZET", "BWG", "AYN", "RRN",
                                                "DTH", "FPF", "HLP", "SSR", "IGR" };

    std::array<std::string, 10> text15_white = { "AMM", "LLT", "DLL", "LLI", "ZDZ",
                                                "MES", "XKF", "BSS", "NKK", "DSR" };

    std::array<std::string, 10> text16_white = { "FYZ", "MDW", "CNI", "XGD", "FGF",
                                                "FXC", "PKG", "MMW", "WCW", "MGB" };

    std::array<std::string, 10> text17_white = { "KMX", "GBA", "DCL", "KZR", "NCA",
                                                "TIT", "XYE", "DHT", "ZET", "RSB" };

    std::array<std::string, 10> text18_white = { "FGH", "GKD", "YAS", "REF", "LXD",
                                                "FFN", "XFK", "TBN", "MBY", "HXE" };

    std::array<std::string, 10> text19_white = { "XAI", "EHW", "FDT", "ZWX", "EES",
                                                "HKX", "XCE", "GAB", "WKD", "LTY" };

    std::array<std::string, 10> text20_white = { "DFZ", "AZG", "FPM", "ZBC", "MWX",
                                                "RWN", "ZSK", "NBM", "AXY", "HME" };


    std::array<std::array<std::string, 10>, 20> all_text_white = { text1_white, text2_white, text3_white, text4_white, text5_white,
                                                                   text6_white, text7_white, text8_white, text9_white, text10_white,
                                                                   text11_white, text12_white, text13_white, text14_white, text15_white,
                                                                   text16_white, text17_white, text18_white, text19_white, text20_white };

    std::vector<Image> all_image_white;

    int counter_fontsize_white = 1;
    for (size_t i = 0; i < all_text_white.size(); i++)
    {
        for (size_t j = 0; j < all_text_white[i].size(); j++)
        {
            Image image(counter_fontsize_white, size1, 2 * counter_fontsize_white, all_text_white[i][j]);
            all_image_white.push_back(image);
        }
        counter_fontsize_white += 1;
    }



    /*------------------------------------------------------------------------------------------------------------------------------------------------------*/



    std::array<std::string, 10> text1_size1 = { "ARI", "GID", "YLE", "CDF", "DXS",
                                                "ZTT", "GTS", "ZLN", "ZWK", "MIC" };

    std::array<std::string, 10> text2_size1 = { "ZHR", "HPB", "LMN", "SMS", "XPL",
                                                "NNE", "FYZ", "YXK", "LSE", "WDN" };

    std::array<std::string, 10> text3_size1 = { "KYW", "XRL", "ALW", "NNB", "EDB",
                                                "ELF", "KNR", "YCT", "FMC", "IYM" };

    std::array<std::string, 10> text4_size1 = { "AFI", "SBB", "EBL", "BPZ", "AXC",
                                                "BZM", "GIA", "ZFD", "RIN", "RRI" };

    std::array<std::string, 10> text5_size1 = { "WDL", "YBT", "LLR", "ZCG", "CSB",
                                                "WBA", "DFM", "LIT", "MSH", "ATN" };

    std::array<std::string, 10> text6_size1 = { "XNP", "FIR", "ZXB", "PTB", "XTT",
                                                "YPS", "WTY", "FFG", "ARA", "FNT" };

    std::array<std::string, 10> text7_size1 = { "WBX", "ZAT", "NMF", "ESP", "ZCI",
                                                "ZMH", "HIR", "DCB", "FBR", "PKW" };

    std::array<std::string, 10> text8_size1 = { "LGT", "HFR", "DRE", "GYY", "WXZ",
                                                "CSL", "LZT", "DAW", "EFL", "WTY" };

    std::array<std::string, 10> text9_size1 = { "CTC", "DDH", "PGT", "LPL", "RCW",
                                                "HTA", "MWN", "CKT", "ZWA", "AIE" };

    std::array<std::string, 10> text10_size1 = { "ZIX", "ZMA", "GBF", "CLT", "LDX",
                                                "HKP", "HXH", "YAT", "RZL", "NXY" };

    std::array<std::string, 10> text11_size1 = { "SEW", "TCL", "MTX", "WSM", "PGA",
                                                "YMY", "PDA", "KME", "KRF", "ZNP" };

    std::array<std::string, 10> text12_size1 = { "CGS", "ZCW", "HML", "EHF", "PZM",
                                                "RTB", "LKZ", "MTL", "PME", "XLR" };

    std::array<std::string, 10> text13_size1 = { "DAA", "WMT", "LAE", "PTL", "XEZ",
                                                "THZ", "WCM", "FCK", "HII", "IDW" };

    std::array<std::string, 10> text14_size1 = { "NEW", "NYF", "GGD", "LWX", "YRB",
                                                "XKK", "SGK", "DKK", "LWW", "YEX" };

    std::array<std::string, 10> text15_size1 = { "GNE", "CIL", "NBG", "CWR", "XYD",
                                                "YHM", "NTE", "IIT", "NDE", "AXF" };

    std::array<std::string, 10> text16_size1 = { "LDW", "RED", "DTE", "KXZ", "BRT",
                                                "CNC", "MDY", "TKE", "KAH", "MYC" };

    std::array<std::string, 10> text17_size1 = { "CNT", "NEX", "KXG", "BGI", "PTI",
                                                "REA", "KFG", "AFS", "BTD", "XTD" };

    std::array<std::string, 10> text18_size1 = { "TTS", "MHW", "IWN", "STW", "AKN",
                                                "GAR", "GLZ", "MIE", "FHY", "KFN" };

    std::array<std::string, 10> text19_size1 = { "WYS", "PIM", "ZTN", "FGK", "NIR",
                                                "HWC", "EAG", "RNK", "TYB", "AMD" };

    std::array<std::string, 10> text20_size1 = { "EHC", "YXI", "KTE", "YYI", "IMT",
                                                "ZTL", "BZM", "FMA", "NEY", "RCH" };


    std::array<std::array<std::string, 10>, 20> all_text_size1 = { text1_size1, text2_size1, text3_size1, text4_size1, text5_size1,
                                                                   text6_size1, text7_size1, text8_size1, text9_size1, text10_size1,
                                                                   text11_size1, text12_size1, text13_size1, text14_size1, text15_size1,
                                                                   text16_size1, text17_size1, text18_size1, text19_size1, text20_size1 };

    std::vector<Image> all_image_size1;

    int counter_fontsize_size1 = 1;
    for (size_t i = 0; i < all_text_size1.size(); i++)
    {
        for (size_t j = 0; j < all_text_size1[i].size(); j++)
        {
            Image image(counter_fontsize_size1, size1, 2 * counter_fontsize_size1, all_text_size1[i][j]);
            all_image_size1.push_back(image);
        }
        counter_fontsize_size1 += 1;
    }



    /*------------------------------------------------------------------------------------------------------------------------------------------------------*/



    std::array<std::string, 10> text1_size2 = { "FMY", "DLD", "NTL", "IGX", "RGY",
                                                "DLC", "GPL", "YZD", "RFC", "RLT" };

    std::array<std::string, 10> text2_size2 = { "GPE", "ETR", "HHK", "TPE", "PFY",
                                                "KII", "LNY", "ZLX", "ABB", "DPM" };

    std::array<std::string, 10> text3_size2 = { "GMZ", "TCR", "MXR", "FBP", "BKK",
                                                "BWE", "CTM", "LDD", "CHH", "YPF" };

    std::array<std::string, 10> text4_size2 = { "KWR", "GNT", "ZAN", "PGP", "DFZ",
                                                "MHT", "SKK", "GWN", "HYW", "SSH" };

    std::array<std::string, 10> text5_size2 = { "FSL", "TKS", "TFT", "RFE", "EPT",
                                                "TMY", "GXZ", "DEY", "RCN", "RFE" };

    std::array<std::string, 10> text6_size2 = { "YFA", "DST", "FXM", "PDZ", "HGE",
                                                "AZH", "GDY", "ZZK", "XDE", "TGI" };

    std::array<std::string, 10> text7_size2 = { "PZG", "ABY", "LET", "RHI", "AMN",
                                                "CSL", "BZG", "RAW", "HEW", "LCB" };

    std::array<std::string, 10> text8_size2 = { "DTT", "YXY", "ZIE", "NYB", "YZC",
                                                "WZC", "WZS", "EAR", "LPS", "HZW" };

    std::array<std::string, 10> text9_size2 = { "LIT", "GDH", "LGW", "SIB", "WMH",
                                                "ENC", "ZLN", "MNS", "ZIG", "ZER" };

    std::array<std::string, 10> text10_size2 = { "LRB", "DXC", "LHK", "FZS", "EWF",
                                                "ZDH", "LYX", "LXH", "BHX", "RGD" };

    std::array<std::string, 10> text11_size2 = { "ZTE", "DNK", "BRK", "WAI", "NMT",
                                                "BXY", "YHG", "IPI", "PZS", "LSC" };

    std::array<std::string, 10> text12_size2 = { "LRX", "STI", "BWB", "LRB", "XDP",
                                                "PCK", "KBW", "SKH", "AZG", "SKY" };

    std::array<std::string, 10> text13_size2 = { "HGG", "LHF", "DKZ", "GCC", "WII",
                                                "DYF", "KGL", "RKZ", "MRZ", "RLH" };

    std::array<std::string, 10> text14_size2 = { "ICR", "SYK", "KSB", "INE", "RMB",
                                                "FTA", "DEK", "BWZ", "PLG", "BXI" };

    std::array<std::string, 10> text15_size2 = { "SAK", "YEW", "DYD", "TTK", "MST",
                                                "FAC", "EPF", "ZRE", "CFG", "PKR" };

    std::array<std::string, 10> text16_size2 = { "NBN", "AYS", "SBP", "TXG", "DGA",
                                                "YKB", "YMR", "BLH", "FNL", "MFY" };

    std::array<std::string, 10> text17_size2 = { "WFL", "KZN", "LCT", "RMD", "PSA",
                                                "HPM", "NSC", "BYH", "SXX", "XZW" };

    std::array<std::string, 10> text18_size2 = { "PEA", "FRZ", "PDZ", "EMB", "XFN",
                                                "ZTG", "ZAW", "LNK", "MNH", "TGC" };

    std::array<std::string, 10> text19_size2 = { "RRS", "FPY", "SHL", "NSW", "SHZ",
                                                "SBB", "LZH", "NKI", "WZK", "BIG" };

    std::array<std::string, 10> text20_size2 = { "RBZ", "KGL", "HZW", "SMK", "KFT",
                                                "KXT", "IIP", "PZB", "YTZ", "GSH" };


    std::array<std::array<std::string, 10>, 20> all_text_size2 = { text1_size2, text2_size2, text3_size2, text4_size2, text5_size2,
                                                                   text6_size2, text7_size2, text8_size2, text9_size2, text10_size2,
                                                                   text11_size2, text12_size2, text13_size2, text14_size2, text15_size2,
                                                                   text16_size2, text17_size2, text18_size2, text19_size2, text20_size2 };

    std::vector<Image> all_image_size2;

    int counter_fontsize_size2 = 1;
    for (size_t i = 0; i < all_text_size2.size(); i++)
    {
        for (size_t j = 0; j < all_text_size2[i].size(); j++)
        {
            Image image(counter_fontsize_size2, size2, 2 * counter_fontsize_size2, all_text_size2[i][j]);
            all_image_size2.push_back(image);
        }
        counter_fontsize_size2 += 1;
    }



    /*------------------------------------------------------------------------------------------------------------------------------------------------------*/



    std::array<std::string, 10> text1_size3 = { "IHZ", "YHT", "LFL", "LEM", "DEA",
                                                "LZK", "AMH", "EWR", "IZZ", "SKR" };

    std::array<std::string, 10> text2_size3 = { "WWY", "SPD", "IAI", "XMP", "INS",
                                                "GBN", "TCC", "CEW", "TNR", "PGC" };

    std::array<std::string, 10> text3_size3 = { "AIX", "YBS", "WEY", "RWK", "XIM",
                                                "FFX", "SDL", "GDF", "YIS", "NDK" };

    std::array<std::string, 10> text4_size3 = { "DBT", "YAW", "PSZ", "KKR", "WEZ",
                                                "HKF", "EEG", "RIH", "XGS", "LTT" };

    std::array<std::string, 10> text5_size3 = { "EDP", "HTL", "SZE", "FID", "GTR",
                                                "NPN", "CZR", "GZP", "WTB", "CNW" };

    std::array<std::string, 10> text6_size3 = { "YTH", "ZCC", "KXB", "NAH", "PGB",
                                                "HTR", "YBM", "LFL", "CZD", "DZT" };

    std::array<std::string, 10> text7_size3 = { "WIF", "STB", "DKS", "BHN", "LAH",
                                                "WXN", "XCF", "ETC", "HEW", "YWL" };

    std::array<std::string, 10> text8_size3 = { "IGR", "YCA", "DTT", "CWE", "XXN",
                                                "KNH", "AHL", "FMF", "FTI", "BSC" };

    std::array<std::string, 10> text9_size3 = { "CHN", "MKC", "WEH", "YHB", "GCC",
                                                "KIC", "PNZ", "TIH", "IPI", "RTY" };

    std::array<std::string, 10> text10_size3 = { "STD", "GHN", "KDS", "TAB", "SGD",
                                                "WSK", "WIA", "RGD", "YKW", "HAP" };

    std::array<std::string, 10> text11_size3 = { "PXC", "SPR", "TGX", "CSG", "SSR",
                                                "YWS", "NCZ", "LSI", "WHL", "CBX" };

    std::array<std::string, 10> text12_size3 = { "TNS", "THI", "KCN", "EFE", "LWX",
                                                "DSR", "WGR", "TSI", "BMP", "KNS" };

    std::array<std::string, 10> text13_size3 = { "THR", "CME", "NGB", "AYC", "MIG",
                                                "BCW", "WYC", "ZEZ", "YLK", "WAY" };

    std::array<std::string, 10> text14_size3 = { "NTG", "DTW", "HFA", "GDY", "HRE",
                                                "PSG", "KMC", "KIH", "KES", "XAS" };

    std::array<std::string, 10> text15_size3 = { "BEG", "WEF", "ZWB", "MZG", "GCP",
                                                "KED", "MLF", "ETG", "ALA", "GFH" };

    std::array<std::string, 10> text16_size3 = { "CEM", "IAP", "MAK", "LKH", "TPH",
                                                "HKZ", "ILY", "PNP", "WNA", "SXF" };

    std::array<std::string, 10> text17_size3 = { "MZW", "ZGM", "EEB", "HTA", "WFI",
                                                "EXZ", "LEM", "PWG", "KET", "GXK" };

    std::array<std::string, 10> text18_size3 = { "YGG", "SEN", "GIT", "FPL", "DHS",
                                                "MMN", "IYR", "ZMI", "DAM", "YGI" };

    std::array<std::string, 10> text19_size3 = { "ADM", "XDP", "ZPP", "NZF", "YZK",
                                                "TRP", "ZRM", "WWM", "RDA", "XLS" };

    std::array<std::string, 10> text20_size3 = { "YIT", "KGZ", "ZDL", "NSK", "SNG",
                                                "EFZ", "WER", "ZFI", "WPM", "SLA" };


    std::array<std::array<std::string, 10>, 20> all_text_size3 = { text1_size3, text2_size3, text3_size3, text4_size3, text5_size3,
                                                                   text6_size3, text7_size3, text8_size3, text9_size3, text10_size3,
                                                                   text11_size3, text12_size3, text13_size3, text14_size3, text15_size3,
                                                                   text16_size3, text17_size3, text18_size3, text19_size3, text20_size3 };

    std::vector<Image> all_image_size3;

    int counter_fontsize_size3 = 1;
    for (size_t i = 0; i < all_text_size3.size(); i++)
    {
        for (size_t j = 0; j < all_text_size3[i].size(); j++)
        {
            Image image(counter_fontsize_size3, size3, 2 * counter_fontsize_size3, all_text_size3[i][j]);
            all_image_size3.push_back(image);
        }
        counter_fontsize_size3 += 1;
    }



/*------------------------------------------------------------------------------------------------------------------------------------------------------*/

    if ((all_image_black.size() != 200) || (all_image_white.size() != 200) || (all_image_size1.size() != 200) || (all_image_size2.size() != 200) || (all_image_size3.size() != 200))
    {
        std::cout << "not load" << std::endl;
        return 1;
    }

    std::string date = "20220209";
    std::string size_string1 = std::to_string(size1);
    std::string size_string2 = std::to_string(size2);
    std::string size_string3 = std::to_string(size3);

    int counter = 1;
    for (size_t i = 0; i < all_image_black.size(); i++)
    {
        std::string font_string = std::to_string(all_image_black[i].fontscale_getter());
        std::string file_name = "-font" + font_string + "-" + std::to_string(counter) + ".bmp";
        cv::imwrite(date + "image/size" + size_string1 + "/size" + size_string1 + file_name, all_image_size1[i].image_getter());
        cv::imwrite(date + "image/size" + size_string2 + "/size" + size_string2 + file_name, all_image_size2[i].image_getter());
        cv::imwrite(date + "image/size" + size_string3 + "/size" + size_string3 + file_name, all_image_size3[i].image_getter());
        cv::imwrite(date + "image/black/black" + file_name, all_image_black[i].black_text_image_getter());
        cv::imwrite(date + "image/white/white" + file_name, all_image_white[i].white_text_image_getter());
        if (counter == 10)
        {
            counter = 0;
        }
        counter++;
    }
    cv::imwrite(date + "image/size" + size_string1 + "/pattern.bmp", all_image_size1[0].pattern_image_getter());
    cv::imwrite(date + "image/size" + size_string2 + "/pattern.bmp", all_image_size2[0].pattern_image_getter());
    cv::imwrite(date + "image/size" + size_string3 + "/pattern.bmp", all_image_size3[0].pattern_image_getter());

}
