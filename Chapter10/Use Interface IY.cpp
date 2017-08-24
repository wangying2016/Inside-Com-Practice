// Send an array to the component.
long arrayIn[] = { 22, 44, 22, 2, 2, 2, 2, 2 };
long sizeIn = sizeof(arrayIn) / sizeof(arrayIn[0]);
HRESULT hr = pIY->FyArrayIn(sizeIn, arrayIn);
assert(SUCCEEDED(hr));

// Get the array back from the component.

// Get the size of the array.
long sizeOut = 0;
hr = pIY->FyCount(&sizeOut);
assert(SUCCEEDED(hr));

// Allocate the array.
long* arrayOut = new long[sizeOut];

// Get the array.
hr = pIY->FyArrayOut(&sizeOut, arrayOut);
assert(SUCCEEDED(hr));

// Display the array returned from the function.
ostrstream sout;
sout << "FyArray returned"
     << sizeOut 
     << "elements:";
for (int i = 0; i < sizeOut; i++) {
    sout << " " << arrayOut[i];
}
sout << "." << ends;
trace(sout.str());

// Cleanup
delete [] arrayOut;