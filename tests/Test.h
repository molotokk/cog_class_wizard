#ifndef TEST_H
#define TEST_H



class Test
{

	public:
		// Property get / set
		void setParameterSetFile(const std::wstring value);
		std::wstring	parameterSetFile() const;

		void setOffset(const cv::Point value);
		cv::Point	offset() const;

		// Methods
		bool	init() ;
		bool	process(const cv::InputArray src1, const cv::InputArray src2, cv::OutputArray dst) ;

	private:
		bool	loadParameters(const std::wstring& filePath) ;
		bool	saveParameters(const std::wstring& filePath) ;

	protected:
		void	performPanSharpening(cv::InputArray visibleMono, cv::InputArray thermal, cv::OutputArray dst, cv::Point offset) ;
		void	translateImage(cv::InputArray src, cv::OutputArray dst, cv::Point offset = cv::Point(0, 0)) ;
		void	zoomImage(cv::InputArray src, cv::OutputArray dst, double factor = 1) ;

	private:
		class	PrivateData;
		std::unique_ptr<PrivateData>	d_data;

	public:
		Test();
		virtual ~Test();
};

#endif //TEST_H
