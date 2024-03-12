// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

using std::string;
using std::ofstream;
using std::stringstream;

class SVG {
private:
	const string name;
	ofstream f;
public:
	SVG(string name) : name(name) {
		f = ofstream(name);
		f << "<svg width=\"500\" height=\"500\""
			<< " xmlns=\"http://www.w3.org/2000/svg\">\n";
	}

	void AddElement(string elem, string params) {
		f << "<" << elem << " " << params << " />\n";
	}

	void Save() {
		f << "</svg>";
		f.close();
	}

};

class Figure {
private:
	int x = 50, y = 50;
	string stroke = "black";  string fill = "green";
public:
	virtual double Perimetr() = 0;
	virtual double GetCenter() = 0;//центр
	virtual double GetRightPoint() = 0; //середина правой стороны
	virtual void AddTo(SVG& s) const = 0;


	int GetX() const { return x; }
	int GetY() const { return y; }

	void SetX(int new_x) { x = new_x; }
	void SetY(int new_y) { y = new_y; }

	string GetFill() const { return fill; }
	string GetStroke() const { return stroke; }

	void SetFill(string color) { fill = color; }
	void SetStroke(string color) { stroke = color; }
};

class Rectangle : public Figure {
private:
	int w = 70, h = 70;
public:
	Rectangle(int x, int y, int w, int h) {
		SetX(x);
		SetY(y);
		this->w = w;
		this->h = h;
	}

	void AddTo(SVG& s) const override {
		stringstream p;
		p << "x='" << GetX() - w / 2 << "' ";        p << "y='" << GetY() - h / 2 << "' ";
		p << "width='" << w << "' ";        p << "height='" << h << "' ";
		p << "stroke='" << GetStroke() << "' ";
		p << "fill='" << GetFill() << "' ";
		s.AddElement("rect", p.str());
	}

	double Perimetr() override {
		return 2 * (w + h);
	}
	double GetCenter() override {
		double centerX = (GetX() + w) / 2;
		double centerY = (GetY() + h) / 2;
		return centerX, centerY;
	}
	double GetRightPoint() override {
		double rightX = w;
		double rightY = (GetY() - h) / 2;
		return rightX, rightY;
	}
};



int main()
{
	SVG s("picture1.svg");
	Rectangle r(20, 0, 70, 70);
	r.SetFill("pink");
	r.AddTo(s);
	std::cout<< r.Perimetr();


	s.Save();
	system("start picture1.svg");
	return 0;
}
