
#include "google/sparsetable"


#include <string>
#include <iostream>
#include <ostream>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/stream.hpp>

//namespace io = boost::iostreams;
//

/*
class logtest
{
public:
	logtest() { std::cout << "logtest::logtest()" << std::endl; };

	void createlog() {
		sbuf.open(boost::iostreams::file_sink(_filename));
		out.rdbuf(&sbuf);

	};
	std::string _filename;
	boost::iostreams::stream_buffer<boost::iostreams::file_sink> sbuf;
	std::ostream  out; 

	void setfile(std::string filename) { if (_filename.empty())  _filename = filename;  }
	void write(std::string logtext) {out  << logtext; };
private:
	
};
*/
int main()
{
	std::string _filename = "foo.txt";
	std::string s1 = "foo.txt";
	std::string s2 = "bar.txt";

		boost::iostreams::stream_buffer<boost::iostreams::file_sink> log(s1);
		std::ostream* pLog = new std::ostream(&log);
		*pLog << "testing 123" << std::endl;

    for (int i = 0; i< 1000000; i++) {

    }
	
/*
	boost::iostreams::stream_buffer<boost::iostreams::file_sink> sbuf;
	boost::iostreams::stream_buffer<boost::iostreams::file_sink> bsbuf;
	std::ostream  out(0); 
	sbuf.open(_filename);
	out.rdbuf(&sbuf);	
	out << "TESTING 123" << std::endl;
*/

	//sbuf.open(boost::iostreams::file_sink(_filename));
	//out.rdbuf(&sbuf);

/*
	logtest l;
	l.setfile("out.txt");
	l.createlog();
	l.write("This is a test");
*/
		
//   boost::iostreams::stream_buffer<boost::iostreams::file_sink> buf("log.txt");
//   std::ostream                     out(&buf);
}


/*
int main()
{
	boost::iostreams::stream_buffer<io::file_sink> buf("log.txt");
	std::ostream out(&buf);	
	//boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));

	for (int i = 0; i < BUFSIZ ; i++) {

		out << i;
	}	
	//t.wait();

	std::cout << "Hello world" << std::endl;

	return 0;

}
*/
/*
int
main()
{
	int lastx = 0;
	int min = 0;
	int x = 0;
	google::sparsetable<int> s(1000000);
	for (int i = 0; i<1000000; i++) {
		x = rand();	
		s[i] = x;
		if (x < lastx)	min = x;
	}
	std::sort(s.begin(), s.end(), operator<(int lhs, int rhs));
	std::cout << s.size() << " ";
	for (int j = 0; j<500; j++) {
		long r = rand();
		if (r < s.size()) {
			std::cout << s[j] << std::endl;
		}	
	}
	std::cout << s[1] << std::endl;
	std::cout << min << std::endl;
};
*/
