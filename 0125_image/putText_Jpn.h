#ifndef PUT_TEXT_JPN_H_
#define PUT_TEXT_JPN_H_


// opencv
#pragma warning(push)
#pragma warning ( disable : 4819 )
#include <opencv2/opencv.hpp>
#pragma warning(pop)

//
#include <tchar.h>

//
namespace sc
{
	namespace myCV
	{
		void putText_Jpn(cv::Mat& a_r_img_dst, std::wstring a_p_text, cv::Point a_pos_org, const TCHAR* a_p_fontname, double a_font_scale, cv::Scalar a_font_color, int a_thickness = 1, int lineType = 8);
	}
}

#endif	// PUT_TEXT_JPN_H_
