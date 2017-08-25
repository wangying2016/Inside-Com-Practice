// Get the dispid for the method
DISPID dispid;
OLECHAR* name = L"FxStringIn";
HRESULT hr = pIDispatch->GetIDsOfNames(IID_NULL,
                &name,
                1,
                GetUserDefaultLCID(),
                &dispid);

// Pass the following string to the component.
wchar_t wszIn[] = L"Test String from client.";

// Convert the wide-character string to a BSTR.
BSTR bstrIn;
bstrIn = ::SysAllocString(wzIn);

// Allocate and initialize a VARIANT argument.
VARIANTARG varg;
::VariantInit(&varg);   // Initialize the VARIANT
varg.vt = VT_BSTR;      // Type of VARIANT data
varg.bstrVal = bstrIn;  // Data for the VARIANT

// Fill in the DISPPARAMS structure.
DISPPARAMS param;
param.cArgs = 1;        // One argument
param.rgarg = &varg;    // Pointer to argument
param.cNamedArgs = 0;   // No named args
param.rgdispidNameArgs = NULL;

hr = pIDispatch->Invoke(dispid,
            IID_NULL,
            GetUserDefaultLCID(),
            DISPATCH_METHOD,
            &param,
            NULL,
            NULL,
            NULL);

// Clean up
::SysFreeString(bstrIn);