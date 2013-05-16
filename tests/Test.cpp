#include "Test.h"

class Test::PrivateData
{
		public:
		int	stereoProcessorType;
		double	factor;
		std::wstring	parameterSetFile;
		cv::Point	offset;
		PrivateData():
			stereoProcessorType()
			, factor(1)
			, parameterSetFile(L"stereoprocessor_parameters.yml")
			, offset(){
		}
};

//-----------------------------------------------------------------------------
Test::Test()  : d_data(new PrivateData())
{

}

Test::~Test()
{

}

// PROPERTIES
//-----------------------------------------------------------------------------
void Test::setParameterSetFile(const std::wstring value)
{
	d_data->parameterSetFile = value;
}

std::wstring	Test::parameterSetFile() const
{
	return d_data->parameterSetFile;
}

//-----------------------------------------------------------------------------
void Test::setOffset(const cv::Point value)
{
	d_data->offset = value;
}

cv::Point	Test::offset() const
{
	return d_data->offset;
}

// PUBLIC METHODS
//-----------------------------------------------------------------------------
bool	Test::init() 
{

}

//-----------------------------------------------------------------------------
bool	Test::process(const cv::InputArray src1, const cv::InputArray src2, cv::OutputArray dst) 
{

}

// PRIVATE METHODS
//-----------------------------------------------------------------------------
bool	Test::loadParameters(const std::wstring& filePath) 
{

}

//-----------------------------------------------------------------------------
bool	Test::saveParameters(const std::wstring& filePath) 
{

}

// PROTECTED METHODS
//-----------------------------------------------------------------------------
void	Test::performPanSharpening(cv::InputArray visibleMono, cv::InputArray thermal, cv::OutputArray dst, cv::Point offset) 
{

}

//-----------------------------------------------------------------------------
void	Test::translateImage(cv::InputArray src, cv::OutputArray dst, cv::Point offset = cv::Point(0, 0)) 
{

}

//-----------------------------------------------------------------------------
void	Test::zoomImage(cv::InputArray src, cv::OutputArray dst, double factor = 1) 
{

}

