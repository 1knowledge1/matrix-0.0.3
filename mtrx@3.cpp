#include<iostream>
#include <sstream>
#include <fstream>
using namespace std;

bool equal(float ** lhs_elements,
	unsigned int lhs_rows,
	unsigned int lhs_columns,
	float ** rhs_elements,
	unsigned int rhs_rows,
	unsigned int rhs_columns)
{
	if ((lhs_rows == rhs_rows) && (lhs_columns == rhs_columns))
	{
		for (unsigned int i = 0; i < lhs_rows; ++i)
			for (unsigned int j = 0; j < lhs_columns; ++j) {
				if (lhs_elements[i][j] == rhs_elements[i][j]) return true;
				else return false;
			}
	}
	else return false;
}

bool transpose(float ** lhs_elements,
	unsigned int lhs_rows,
	unsigned int lhs_columns,
	float ** & result_elements,
	unsigned int & result_rows,
	unsigned int & result_columns)
{
	result_rows = lhs_columns;
	result_columns = lhs_rows;

	for (unsigned int i = 0; i < lhs_columns; ++i)
		for (unsigned int j = 0; j < lhs_rows; ++j) {
			result_elements[i][j] = lhs_elements[j][i];
		}
	return true;
}

bool truncate(float ** lhs_elements,
	unsigned int lhs_rows,
	unsigned int lhs_columns,
	unsigned int cut_rows,
	unsigned int cut_columns,
	float ** & result_elements)
{
	if (lhs_rows == lhs_columns) {

		for (unsigned int i = 0, k = 0; i < lhs_rows; ++i) {
			if (i == cut_rows) continue;
			for (unsigned int j = 0, m = 0; j < lhs_columns; ++j) {
				if (j == cut_columns) continue;
				result_elements[k][m] = lhs_elements[i][j];
				m++;
			}
			k++;
		}
		return true;
	}
	else return false;
}

float determinant(float ** lhs_elements,
	unsigned int lhs_rows)
{
	int i, d = 0, k = 1, n = lhs_rows - 1, j = 0;

	float **p;
	p = new float*[lhs_rows];
	for (int i = 0; i<lhs_rows; i++) {
		p[i] = new float[lhs_rows];
	}

	if (lhs_rows < 1) {
		cout << "An error has occured while reading input data";
		exit(0);
	}
	if (lhs_rows == 1) {
		d = lhs_elements[0][0];
		return(d);
	}
	if (lhs_rows == 2) {
		d = lhs_elements[0][0] * lhs_elements[1][1] - (lhs_elements[1][0] * lhs_elements[0][1]);
		return(d);
	}
	if (lhs_rows > 2) {
		for (i = 0; i<lhs_rows; i++) {
			truncate(lhs_elements, lhs_rows, lhs_rows, i, 0, p);
			d = d + k * lhs_elements[i][0] * determinant(p, n);
			k = -k;
		}
	}
	for (int i = 0; i<lhs_rows; i++) {
		delete[] p[i];
	}
	delete[] p;

	return(d);
}

bool reverse(float ** lhs_elements,
	unsigned int lhs_rows,
	unsigned int lhs_columns,
	float ** & result_elements,
	unsigned int & result_rows,
	unsigned int & result_columns)
{
	if (lhs_rows == lhs_columns) {
		if (determinant(lhs_elements, lhs_rows) != 0) {
			double temp;

			double **E = new double *[lhs_rows];

			for (int i = 0; i < lhs_rows; i++)
				E[i] = new double[lhs_rows];

			for (int i = 0; i < lhs_rows; i++)
				for (int j = 0; j < lhs_rows; j++)
				{
					E[i][j] = 0.0;

					if (i == j)
						E[i][j] = 1.0;
				}

			for (int k = 0; k < lhs_rows; k++)
			{
				temp = lhs_elements[k][k];

				for (int j = 0; j < lhs_rows; j++)
				{
					lhs_elements[k][j] /= temp;
					E[k][j] /= temp;
				}

				for (int i = k + 1; i < lhs_rows; i++)
				{
					temp = lhs_elements[i][k];

					for (int j = 0; j < lhs_rows; j++)
					{
						lhs_elements[i][j] -= lhs_elements[k][j] * temp;
						E[i][j] -= E[k][j] * temp;
					}
				}
			}

			for (int k = lhs_rows - 1; k > 0; k--)
			{
				for (int i = k - 1; i >= 0; i--)
				{
					temp = lhs_elements[i][k];

					for (int j = 0; j < lhs_rows; j++)
					{
						lhs_elements[i][j] -= lhs_elements[k][j] * temp;
						E[i][j] -= E[k][j] * temp;
					}
				}
			}

			for (int i = 0; i < lhs_rows; i++)
				for (int j = 0; j < lhs_rows; j++)
					lhs_elements[i][j] = E[i][j];

			for (int i = 0; i < lhs_rows; i++)
				delete[] E[i];

			delete[] E;

			return true;
		}
		else {
			cout << "There is no reverse matrix" << endl;
			return false;
		}
	}
	else {
		cout << "There is no reverse matrix" << endl;
		return false;
	}
}

bool add(float ** lhs_elements,
	unsigned int lhs_rows,
	unsigned int lhs_columns,
	float ** rhs_elements,
	unsigned int rhs_rows,
	unsigned int rhs_columns,
	float ** & result_elements,
	unsigned int & result_rows,
	unsigned int & result_columns)
{
	if (lhs_rows == rhs_rows && lhs_columns == rhs_columns) {
		for (int i = 0; i < lhs_rows; i++) {
			for (int j = 0; j < lhs_columns; j++) {
				result_elements[i][j] = lhs_elements[i][j] + rhs_elements[i][j];
			}
		}
		result_rows = lhs_rows;
		result_columns = lhs_columns;
		return true;
	}
	else return false;
}

bool sub(float ** lhs_elements,
	unsigned int lhs_rows,
	unsigned int lhs_columns,
	float ** rhs_elements,
	unsigned int rhs_rows,
	unsigned int rhs_columns,
	float ** & result_elements,
	unsigned int & result_rows,
	unsigned int & result_columns)
{
	if (lhs_rows == rhs_rows && lhs_columns == rhs_columns) {
		for (int i = 0; i < lhs_rows; i++) {
			for (int j = 0; j < lhs_columns; j++) {
				result_elements[i][j] = lhs_elements[i][j] - rhs_elements[i][j];
			}
		}
		result_rows = lhs_rows;
		result_columns = lhs_columns;
		return true;
	}
	else return false;
}

bool multiply(float ** lhs_elements,
	unsigned int lhs_rows,
	unsigned int lhs_columns,
	float ** rhs_elements,
	unsigned int rhs_rows,
	unsigned int rhs_columns,
	float ** & result_elements,
	unsigned int & result_rows,
	unsigned int & result_columns)
{
	if (lhs_columns == rhs_rows) {
		for (int i = 0; i < lhs_rows; i++) {
			for (int j = 0; j < rhs_columns; j++) {
				result_elements[i][j] = 0;
				for (int k = 0; k < lhs_columns; k++)
					result_elements[i][j] += (lhs_elements[i][k] * rhs_elements[k][j]);
			}
		}
		return true;
	}
	else return false;
}

void destroy(float ** elements,
	unsigned int rows)
{
	for (unsigned int i = 0; i < rows; ++i) {
		delete[] elements[i];
	}
	delete[] elements;
}

auto input(ifstream & stream,
	float ** & result_elements,
	unsigned int & result_rows,
	unsigned int & result_columns) -> istream &
{
	char symbol;
	bool success = true;
	unsigned int rows;
	unsigned int columns;

	if (stream >> rows && stream >> symbol && symbol == ',' && stream >> columns);
	else {
		stream.setstate(std::ios::failbit);
		success = false;
		return stream;
	}

	string str;
	float ** elements;

	elements = new float *[rows];

	for (unsigned int i = 0; i < rows; ++i) {
		elements[i] = new float[columns];
		getline(stream, str);
		for (unsigned int j = 0; j < columns; ++j) {
			if (!(stream >> elements[i][j])) {
				stream.setstate(std::ios::failbit);
				success = false;
				return stream;
			}
		}
	}

	if (success) {
		result_elements = elements;
		result_rows = rows;
		result_columns = columns;
	}
	return stream;
}

auto output(std::ostream & stream,
	float ** elements,
	unsigned int rows,
	unsigned int columns)->std::ostream &
{
	stream << endl;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j) {
			stream << elements[i][j] << ' ';
		}
		stream << endl;
	}
	return stream;
}

auto create(unsigned int rows,
	unsigned int columns,
	float filler = 0.0f) -> float **
{
	float ** elements = new float *[rows];
	for (unsigned int i = 0; i < rows; ++i) {
		elements[i] = new float[columns];
		for (unsigned int j = 0; j < columns; ++j) {
			elements[i][j] = filler;
		}
	}
	return elements;
}

void finput()
{
	ofstream fout;
	fout.open("A.txt");
	fout << "A.txt\n3, 3\n2 2 2\n2 2 2\n2 2 2";
	fout.close();

	fout.open("B.txt");
	fout << "B.txt\n3, 3\n1 1 1\n1 1 1\n1 1 1";
	fout.close();

	fout.open("C.txt");
	fout << "C.txt\n3, 3\n1 2 2\n0 4 4\n0 4 0";
	fout.close();

	fout.open("D.txt");
	fout << "D.txt\n3, 3\n1 2 3\n4 5 6\n7 8 9";
	fout.close();


}
bool readfile(string str,
	float ** & elements,
	unsigned int & rows,
	unsigned int & columns)
{
	ifstream fin;
	string line;
	
		fin.open(str);
		if (!fin.is_open())
		{
			return false;
		}
		getline(fin, line);
		if (!(input(fin, elements, rows, columns)))
		{
			return false;
		}
		fin.close();
		return true;
	
	
}

int main() {
	float ** lhs_elements = nullptr, ** rhs_elements = nullptr , **result_elements;
	unsigned int lhs_rows, rhs_rows = 0, result_rows;
	unsigned int lhs_columns, rhs_columns = 0, result_columns;
	char op;
	finput();

	string str, name1;
	getline(cin, str);
	int num;
	for (num = 0; (str[num] != ' ') && (str[num] != '+') && (str[num] != '-') && (str[num] != '*'); num++)
	{
		name1 =name1 + str[num];
	}
	for (; (str[num] != '+') && (str[num] != '-') && (str[num] != '*')&& (str[num] != 'T') && (str[num] != 'R'); num++);
	op = str[num];
	if ((op != 'T') && (op != 'R'))
	{
		string name2;
		num++;
		while (str[num] == ' ') num++;
		for (; num < str.length(); num++)
		{
			name2 += str[num];
		}
		if (!(readfile(name2, rhs_elements, rhs_rows, rhs_columns)))
		{
			cout << "An error has occured while reading input data.\n";
			return 0;
		}
	}

	if (!(readfile(name1, lhs_elements, lhs_rows, lhs_columns)))
	{
		cout << "An error has occured while reading input data.\n";
		return 0;
	}
	
	switch (op) {
	case '+': {
		if (lhs_rows == rhs_rows && lhs_columns == rhs_columns) {
			result_elements = create(lhs_rows, lhs_columns);
			if (add(lhs_elements,
				lhs_rows,
				lhs_columns,
				rhs_elements,
				rhs_rows,
				rhs_columns,
				result_elements,
				result_rows,
				result_columns)) {

				output(cout, result_elements, result_rows, result_columns);
				destroy(lhs_elements, lhs_rows);
				destroy(rhs_elements, rhs_rows);
				destroy(result_elements, result_rows);
			}
		}
		else {
			cout << "An error has occured while reading input data.\n";
			return 0;
		}
		break;
	}
	case '-': {
		if (lhs_rows == rhs_rows && lhs_columns == rhs_columns) {
			result_elements = create(lhs_rows, lhs_columns);
			if (sub(lhs_elements,
				lhs_rows,
				lhs_columns,
				rhs_elements,
				rhs_rows,
				rhs_columns,
				result_elements,
				result_rows,
				result_columns)) {

				output(cout, result_elements, result_rows, result_columns);
				destroy(lhs_elements, lhs_rows);
				destroy(rhs_elements, rhs_rows);
				destroy(result_elements, result_rows);
			}

		}
		else {
			cout << "An error has occured while reading input data.\n";
			return 0;
		}
		break;
	}
	case '*': {
		if (lhs_columns == rhs_rows) {
			result_elements = create(lhs_rows, rhs_columns);
			result_rows = lhs_rows;
			result_columns = rhs_columns;

			if (multiply(lhs_elements,
				lhs_rows,
				lhs_columns,
				rhs_elements,
				rhs_rows,
				rhs_columns,
				result_elements,
				result_rows,
				result_columns)) {

				output(cout, result_elements, result_rows, result_columns);
				destroy(lhs_elements, lhs_rows);
				destroy(rhs_elements, rhs_rows);
				destroy(result_elements, result_rows);
			}

		}
		else {
			cout << "An error has occured while reading input data.\n";
			return 0;
		}
		break;
	}
	case 'T': {
		result_elements = create(lhs_columns, lhs_rows);
		if (transpose(lhs_elements,
			lhs_rows,
			lhs_columns,
			result_elements,
			result_rows,
			result_columns)) {

			output(cout, result_elements, result_rows, result_columns);
			destroy(lhs_elements, lhs_rows);
			destroy(result_elements, result_rows);
		}
		else {
			cout << "An error has occured while reading input data.\n";
			return 0;
		}
		break;
	}
	case 'R': {
		if (lhs_rows == lhs_columns) {
			if (reverse(lhs_elements,
				lhs_rows,
				lhs_columns,
				lhs_elements,
				lhs_rows,
				lhs_columns)) {

				output(cout, lhs_elements, lhs_rows, lhs_columns);
				destroy(lhs_elements, lhs_rows);
			}
		}
		else {
			cout << "An error has occured while reading input data.\n";
			return 0;
		}
		break;
	}
	default:
		cout << "An error has occured while reading input data.\n";
		return 0;
	}
	
	return 0;
}
