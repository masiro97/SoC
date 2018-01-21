#include "StdAfx.h"
#include "LoadImageFromFileDialog.h"

ByteImage LoadImageFromDialog()
{
	ByteImage image;	// ��ȯ�� ����

	// ���� ��ȭ���ڿ��� BMP ������ ���ϸ� ���̵��� �ϴ� ������ ����
	char szFilter[] = "BMP File (*.BMP) | *.BMP; | All Files(*.*)|*.*||";	

	// �Է� ���� �б�
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);
	if (IDOK != dlg.DoModal()) // ��ȭ ���� ����
	{
		return image;
	}
	CString strPathName = dlg.GetPathName(); // ���� ���� ��� ȹ��
	image.LoadImage(strPathName); // ���� �б�

	return image;
}