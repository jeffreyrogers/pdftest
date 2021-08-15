#include <iostream>

#include <fpdfview.h>

void CheckError() {
    unsigned long err = FPDF_GetLastError();
    std:: cerr << "Load pdf doc unsuccessful: ";
    switch (err) {
        case FPDF_ERR_UNKNOWN:
            std::cerr << "Unknown error";
        break;
        case FPDF_ERR_FILE:
            std::cerr << "File not found or could not be opened";
            break;
        case FPDF_ERR_FORMAT:
            std::cerr << "File not in PDF format or corrupted";
            break;
        case FPDF_ERR_PASSWORD:
            std::cerr << "Password required or incorrect password";
            break;
        case FPDF_ERR_SECURITY:
            std::cerr << "Unsupported security scheme";
            break;
        case FPDF_ERR_PAGE:
            std::cerr << "Page not found or content error";
            break;
        default:
            std::cerr << "Unknown error " << err;
    }
    std::cerr << "." << std::endl;
}

int main() {
    int num_pages;
    FPDF_PAGE page;

    FPDF_LIBRARY_CONFIG config;
    config.version = 3;
    config.m_pUserFontPaths = NULL;
    config.m_pIsolate = NULL;
    config.m_v8EmbedderSlot = 0;
    FPDF_InitLibraryWithConfig(&config);

    FPDF_STRING test_doc = "test.pdf";
    FPDF_DOCUMENT doc = FPDF_LoadDocument(test_doc, nullptr);
    if (!doc) {
        CheckError();
        goto EXIT;
    }

    num_pages = FPDF_GetPageCount(doc);
    if (num_pages == 1) {
        std::cout << "There is " << num_pages << " page in the document" << std::endl;
    } else {
        std::cout << "There are " << num_pages << " pages in the document" << std::endl;
    }
    page = FPDF_LoadPage(doc, 0);

    FPDF_CloseDocument(doc);
EXIT:
    FPDF_DestroyLibrary();
    return 0;
}

