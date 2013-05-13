#include PanSharpener.h

class PanSharpener::PrivateData
{
		public:
		int	stereoProcessorType;
		double	factor;
		std::wstring	parameterSetFile;
		cv::Point	offset;
		PrivateData():
			stereoProcessorType(0)
			, factor(1)
			, parameterSetFile(L"stereoprocessor_parameters.yml")
			, offset(){
		}
};

//-----------------------------------------------------------------------------
PanSharpener::PanSharpener()  : d_data(new PrivateData())
{

}

PanSharpener::~PanSharpener()
{

}

// PROPERTIES
//-----------------------------------------------------------------------------
void PanSharpener::setParameterSetFile(const std::wstring value)
{
	d_data->parameterSetFile = value;
}
std::wstring	PanSharpener::parameterSetFile() const
{
	return d_data->parameterSetFile;
}
//-----------------------------------------------------------------------------
void PanSharpener::setOffset(const cv::Point value)
{
	d_data->offset = value;
}
cv::Point	PanSharpener::offset() const
{
	return d_data->offset;
}
// PUBLIC METHODS
//-----------------------------------------------------------------------------
bool	PanSharpener::init()
{

}

//-----------------------------------------------------------------------------
bool	PanSharpener::process(const cv::InputArray src1, const cv::InputArray src2, cv::OutputArray dst)
{

}

// PRIVATE METHODS
//-----------------------------------------------------------------------------
bool	PanSharpener::loadParameters(const std::wstring& filePath)
{

}

//-----------------------------------------------------------------------------
bool	PanSharpener::saveParameters(const std::wstring& filePath)
{

}

// PROTECTED METHODS
//-----------------------------------------------------------------------------
void	PanSharpener::performPanSharpening(cv::InputArray visibleMono, cv::InputArray thermal, cv::OutputArray dst, cv::Point offset = cv::Point(0, 0))
{

}

//-----------------------------------------------------------------------------
void	PanSharpener::translateImage(cv::InputArray src, cv::OutputArray dst, cv::Point offset = cv::Point(0, 0))
{

}

//-----------------------------------------------------------------------------
void	PanSharpener::zoomImage(cv::InputArray src, cv::OutputArray dst, double factor = 1)
{

}

