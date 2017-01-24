#include "projektDlg.h"

#include <omp.h>


void defaultOperation(wxImage* result, wxImage* image1, wxImage* image2, int i, int n);
void enterLeft(wxImage* result, wxImage* image1, wxImage* image2, int i, int n);
void enterRight(wxImage* result, wxImage* image1, wxImage* image2, int i, int n);
void enterUp(wxImage* result, wxImage* image1, wxImage* image2, int i, int n);
void enterDown(wxImage* result, wxImage* image1, wxImage* image2, int i, int n);
void transition(wxImage* result, wxImage* image1, wxImage* image2, int i, int n);
void horizontalFlip(wxImage* result, wxImage* image1, wxImage* image2, int i, int n);
void verticalFlip(wxImage* result, wxImage* image1, wxImage* image2, int i, int n);
