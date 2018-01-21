#pragma once

#include <windows.h>
#include <assert.h>//assert��ũ�� ���� ���â�� �����

#define CLIP(x) (x < 0)? 0 : x > 255 ? 255 : x
#define PI 3.14


class B_size {
public:
	int width;
	int height;

	B_size(int Width, int Height) {
		width = Width;
		height = Height;
	}

};
class BlauPoint
{
public:
	int x, y;
	BlauPoint(int X = 0, int Y = 0)
	{
		x = X;
		y = Y;
	}
};
class B_Rect {
public:
	int left_x;
	int left_y;
	int right_x;
	int right_y;
	int width;
	int height;

	B_Rect(int nx, int ny, int nwidth, int nheight) {
		left_x = nx;
		left_y = ny;
		right_x = left_x + nwidth;
		right_y = left_y + nheight;
		width = nwidth;
		height = nheight;

	}
	B_Rect(BlauPoint P1, BlauPoint P2) {
		left_x = P1.x;
		left_y = P1.y;
		right_x = P2.x;
		right_y = P2.y;
		width = right_x - left_x;
		height = right_y - right_y;
	}
};
class BlauScalar
{
public:
	int B;
	int G;
	int R;

	int V;

	BlauScalar(int b, int g = 0, int r = 0)
	{
		B = b;
		G = g;
		R = r;
	}
	BlauScalar(int value)
	{
		V = value;
	}
};


template<class T>
class BlauImage
{
protected:
	int nChannels;//ä�� ��
	int Height;//���� �ȼ� ��
	int Width;//���� �ȼ� ��
	int nWStep;//��� ������ ���� �� nWStep = ((Width*nChannels*sizeof(T)+3)&~3)/sizeof(T)
	//int depth;
	T* pImageData;//�ȼ������͸� ����Ű�� ������

public:
	//Getter �Լ�
	int GetChannel() const { return nChannels; }
	int GetHeight() const { return Height; }
	int GetWidth() const { return Width; }
	int GetWStep() const { return nWStep; }
	//int GetDepth() const { return depth; }
	T* GetPtr(int r = 0, int c = 0) const { return pImageData + r*nWStep + c; }

	BlauImage(void) :nChannels(0), Height(0), Width(0), nWStep(0), pImageData(NULL) {}//�⺻ ������
	BlauImage(int width, int height, int channels = 1)//�Ҵ������
		:nChannels(channels), Width(width), Height(height)
		, nWStep(((Width*nChannels * sizeof(T) + 3)&~3) / sizeof(T))
	{
		pImageData = new T[Height*nWStep];
	}
	BlauImage(const BlauImage& img)//���������
	{
		nChannels = img.nChannels;
		Height = img.Height;	 Width = img.Width;	nWStep = img.nWStep;
		pImageData = new T[Height*nWStep];

		memcpy(pImageData, img.pImageData, Height*nWStep * sizeof(T));
	}
	template<class From>
	BlauImage(const BlauImage<From>& img)//��ȯ ������
	{
		nChannels = img.GetChannel();
		Height = img.GetHeight();	 Width = img.GetWidth();
		nWStep = ((Width*nChannels * sizeof(T) + 3)&~3) / sizeof(T);//��� �����Ϳ��Ҽ� �ٽð��
		pImageData = new T[Height*nWStep];

		int wstep = img.GetWStep();

		if (sizeof(T) == 1)
		{
			for (int r = 0; r < Height; r++)
			{
				T* pDst = GetPtr(r);
				From* pSrc = img.GetPtr(r);
				for (int c = 0; c < wstep; c++)
				{
					pDst[c] = (T)CLIP(pSrc[c]);//CLIP-->?
				}
			}
		}
		else
		{
			for (int r = 0; r < Height; r++)
			{
				T* pDst = GetPtr(r);
				From* pSrc = img.GetPtr(r);
				for (int c = 0; c < wstep; c++)
				{
					pDst[c] = (T)pSrc[c];
				}
			}
		}
	}

	~BlauImage(void) { if (pImageData) delete[] pImageData; }//�⺻�Ҹ���

	//Application
	inline T& GetAt(int x, int y, int c = 0) const//�ȼ������Լ�
	{
		assert(x >= 0 && x < Width&&y >= 0 && y < Height);
		return pImageData[nWStep*y + nChannels*x + c];
	}

	void SetConstValue(T val)//�̹����� Ư�������� �ʱ�ȭ�ϴ� �Լ�
	{
		if (val == 0)
		{
			memset(pImageData, 0, nWStep*Height * sizeof(T));
			return;
		}

		if (sizeof(T) == 1)//�������� ������ BYTE
		{
			memset(pImageData, val, nWStep*Height * sizeof(T));
		}
		else
		{
			T* pData = pImageData;
			for (int r = 0; r < Height; r++)
			{
				for (int c = 0; c < Width; c++)//�� nwstep�� �ƴ� width�ΰ�?
				{
					pData[c] = val;
				}
				pData += nWStep;
			}
		}
	}

	bool IsEmpty() const { return pImageData ? false : true; }

	//Operator overloading
	BlauImage& operator=(const BlauImage& img)
	{
		if (this == &img) return *this;

		nChannels = img.nChannels;
		Height = img.Height;	Width = img.Width;	nWStep = img.nWStep;

		if (pImageData) delete[] pImageData;

		if (img.pImageData != NULL)
		{
			pImageData = new T[Height*nWStep];
			memcpy(pImageData, img.pImageData, Height*nWStep * sizeof(T));
		}

		return *this;
	}

	//Save&Load
	bool LoadImage(const char* filename)
	{
		assert(sizeof(T) == 1);//BYTE���� ��츸 ����

		if (strcmp(".BMP", &filename[strlen(filename) - 4]))
		{
			FILE* pFile = NULL;
			fopen_s(&pFile, filename, "rb");//���̳ʸ� �б���
			if (!pFile) return false;

			BITMAPFILEHEADER fileHeader;
			if (!fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, pFile))
			{
				fclose(pFile);
				return false;
			}
			if (fileHeader.bfType != 0x4D42)//BM���ڰ˻�
			{
				fclose(pFile);
				return false;
			}

			BITMAPINFOHEADER infoHeader;
			if (!fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, pFile))
			{
				fclose(pFile);
				return false;
			}
			if (infoHeader.biBitCount != 8 && infoHeader.biBitCount != 24)//ȸ���� �Ǵ� Ʈ���÷��� �ν�
			{
				fclose(pFile);
				return false;
			}

			if (Width != infoHeader.biWidth || Height != infoHeader.biHeight || nChannels != infoHeader.biBitCount / 8)
			{
				if (pImageData) delete[] pImageData;

				nChannels = infoHeader.biBitCount / 8;
				Height = infoHeader.biHeight;
				Width = infoHeader.biWidth;
				nWStep = (Width*nChannels * sizeof(T) + 3)&~3;

				pImageData = new T[Height*nWStep];
			}

			fseek(pFile, fileHeader.bfOffBits, SEEK_SET);

			int r;
			for (r = Height - 1; r >= 0; r--)
			{
				if (!fread(&pImageData[r*nWStep], sizeof(BYTE), nWStep, pFile))
				{
					fclose(pFile);
					return false;
				}
			}

			fclose(pFile);
			return true;
		}
		else
		{
			return false;
		}
	}
	bool SaveImage(const char* filename)
	{
		assert(sizeof(T) == 1);

		if (strcmp(".BMP", &filename[strlen(filename) - 4]))
		{
			FILE* pFile = NULL;
			fopen_s(&pFile, filename, "wb");
			if (!pFile) return false;

			BITMAPFILEHEADER fileHeader;
			fileHeader.bfType = 0x4D42;//"BM"
			fileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + nWStep*Height + (nChannels == 1) * 1024;
			fileHeader.bfReserved1 = 0; fileHeader.bfReserved2 = 0;
			fileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (nChannels == 1) * 256 * sizeof(RGBQUAD);

			fwrite(&fileHeader, sizeof(BITMAPFILEHEADER), 1, pFIle);

			BITMAPINFOHEADER infoHeader;
			infoHeader.biSize = sizeof(BITMAPINFOHEADER);
			infoHeader.biWidth = Width;
			infoHeader.biHeight = Height;
			infoHeader.biPlanes = 1;
			infoHeader.biBitCount = nChannels * 8;
			infoHeader.biCompression = BI_RGB;
			infoHeader.biSizeImage = nWStep*Height;
			infoHeader.biClrImportant = 0;
			infoHeader.biClrUsed = 0;
			infoHeader.biXPelsPerMeter = 0;
			infoHeader.biYPelsPerMeter = 0;

			fwrite(&infoHeader, sizeof(BITMAPINFOHEADER), 1, pFile);

			if (nChannels == 1)
			{
				for (int l = 0; l < 256; l++)
				{
					RGBQUAD GrayPalette = { l,l,l,0 };
					fwrite(&GraPalette, sizeof(RGBQUAD), 1, pFile);
				}
			}

			int r;
			for (r = Height; r >= 0; r--)	fwrite(&pImageData[r*nWStep], sizeof(BYTE), nWStep, pFile);

			fclose(pFile);
			return true;
		}
		else
		{
			return false;
		}
	}

	void BlauCircle(ByteImage& img, BlauPoint center, int radius, BlauScalar Scalar) {
		
		int x1, y1, x2, y2, degree;
		double radian;

		for (degree = 0; degree <= 90;degree++) {

			radian = degree*PI / 180;
			x1 = center.x + radius*cos(radian);
			y1 = center.y + radius*sin(radian);
			x2 = x1 - 2 * radius*cos(radian);
			y2 = y1 - 2 * radius*sin(radian);

			if (img.GetChannel() == 3) {
				img.GetAt(x1, y1, 0) = Scalar.B;
				img.GetAt(x1, y1, 0) = Scalar.G;
				img.GetAt(x1, y1, 0) = Scalar.R;

				img.GetAt(x1, y2, 0) = Scalar.B;
				img.GetAt(x1, y2, 0) = Scalar.G;
				img.GetAt(x1, y2, 0) = Scalar.R;

				img.GetAt(x2, y1, 0) = Scalar.B;
				img.GetAt(x2, y1, 0) = Scalar.G;
				img.GetAt(x2, y1, 0) = Scalar.R;

				img.GetAt(x2, y2, 0) = Scalar.B;
				img.GetAt(x2, y2, 0) = Scalar.G;
				img.GetAt(x2, y2, 0) = Scalar.R;
			}
			if (img.GetChannel() == 1) {
				img.GetAt(x1, y1, 0) = Scalar.V;
				img.GetAt(x1, y2, 0) = Scalar.V;
				img.GetAt(x2, y1, 0) = Scalar.V;
				img.GetAt(x2, y2, 0) = Scalar.V;
			}
		}
	}
};



typedef BlauImage <BYTE   > ByteImage;
typedef BlauImage <int    > IntImage;
typedef BlauImage <float  > FloatImage;
typedef BlauImage <double > DoubleImage;

ByteImage* B_CreateImage(B_size S, int ch) 
{
	
	ByteImage img(S.width, S.height,ch);
	return &img;
}

void B_ReleaseImage(ByteImage **image) {
	
	delete image;
}