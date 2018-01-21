#include <windows.h>
#include <windef.h>//BYTE�� ���ǵǾ� ����
#include <assert.h>//assert��ũ�� ���� ���â�� �����


typedef BlauImage<BYTE> ByteImage;
typedef BlauImage<int> IntImage;
typedef BlauImage<float> FloatImage;
typedef BlauImage<double> DoubleImage;

template<class T>
class BlauImage
{
protected:
	int nChannels;//ä�� ��
	int Height;//���� �ȼ� ��
	int Width;//���� �ȼ� ��
	int nWStep;//��� ������ ���� �� nWStep = ((Width*nChannels*sizeof(T)+3)&~3)/sizeof(T)
	T* pImageData;//�ȼ������͸� ����Ű�� ������

public:
	//Getter �Լ�
	int GetChannel() const { return nChannels; }
	int GetHeight() const { return Height; }
	int GetWidth() const { return Width; }
	int GetWStep() const { return nWStep; }
	T* GetPtr(int r = 0, int c = 0) const { return pImageData + r*nWStep + c; }

	BlauImage(void) :nChannels(0), Height(0), Width(0), nWStep(0), pImageData(NULL) {}//�⺻ ������
	BlauImage(int width, int height, int channels = 1)//�Ҵ������
		:nChannels(channels), Width(width), Height(height)
		, nWStep(((Width*nChannels*sizeof(T) + 3)&~3) / sizeof(T))
	{
		pImageData = new T[Height*nWStep];
	}
	BlauImage(const BlauImage& img)//���������
	{
		nChannels = img.nChannels;
		Height = img.Height;	 Width = img.Width;	nWStep = img.nWStep;
		pImageData = new T[Height*nWStep];

		memcpy(pImageData, img.pImageData, Height*nWStep*sizeof(T));
	}
	template<class From>
	BlauImage(const BlauImage<From>& img)//��ȯ ������
	{
		nChannels = img.GetChannel();
		Height = img.GetHeight();	 Width = img.GetWidth();
		nWStep = ((Width*nChannels*sizeof(T) + 3)&~3) / sizeof(T);//��� �����Ϳ��Ҽ� �ٽð��
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
			memset(pImageData, 0, nWStep*Height*sizeof(T));
			return;
		}

		if (sizeof(T) == 1)//�������� ������ BYTE
		{
			memset(pImageData, val, nWStep*Height*sizeof(T));
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

	bool IsEmpty() const return pImageData ? false : true;

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
			memcpy(pImageData, img.pImageData, Height*nWStep*sizeof(T));
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
				nWStep = (Width*nChannels*sizeof(T) + 3)&~3;

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
};
