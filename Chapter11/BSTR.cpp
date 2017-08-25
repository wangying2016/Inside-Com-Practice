wchar_t wsz[] = L"Threre's the count.";
BSTR bstr;
bstr = SysAllocString(wsz);

SysFreeString(bstr);