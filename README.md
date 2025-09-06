# Vuforia

[Android][Kotlin]Vuforia][AR] Tried running Vuforia's sample code (Image Target).

# Abstract
- Built and ran the Vuforia sample code.
- Explained the code.

# Background
On a whim, I decided to try running Vuforia again.
I'd previously written this [article](https://zenn.dev/rg687076/articles/3a27d02caadee9) explaining how to get it working, but this time... it just wouldn't run. The build kept failing.
With Android Gradle Plugin now in the 8.x series, older code throws build errors left and right. Even the code on GitHub is broken.
Glad to see Vuforia is still offering the service, but even their official sample code won't build.

So?I fixed the build and published it on GitHub.  
The goal this time was again this
![](https://storage.googleapis.com/zenn-user-upload/fd0d9ec59b7e-20220624.png)

# Setup
- Android device
- Development PC (with Android Studio installed)
- Connect Android device and enable debugging
- Download SDK and sample code
  - Vuforia SDK: https://developer.vuforia.com/downloads/sdk
  - Samples: https://developer.vuforia.com/downloads/samples
    - vuforia-sample-android-11-3-4.zip
    - vuforia-sdk-android-11-3-4.zip
- Create a Vuforia account (see Step 1 from [previous guide](https://zenn.dev/rg687076/articles/3a27d02caadee9))
- Get your Vuforia license key (see Step 2 from [previous guide](https://zenn.dev/rg687076/articles/3a27d02caadee9))

# Build Instructions
## 1. Download the modified code I committed here:
https://github.com/aaaa1597/AndKot-VuforiaImageTargetSample

## 2. Open the project in Android Studio
<img src="https://storage.googleapis.com/zenn-user-upload/975f44ccec4e-20220624.png" width="600" />
Click "Open"

<img src="https://storage.googleapis.com/zenn-user-upload/045aff23fa3e-20220624.png" width="600" />
Open the Android project shown above.  
Wait until the project finishes loading.

## 3. Set up authentication info and build
[Vuforia License Page](https://developer.vuforia.com/vui/develop/licenses)

<img src="https://storage.googleapis.com/zenn-user-upload/ca8fccbe4230-20220624.png" width="600" />
In Android Studio, open AppController.cpp and paste the license key you copied in Step 2 into licenseKey.  
Then build.
If you skip this step, you'll get the following error when launching the app:
<img src="https://storage.googleapis.com/zenn-user-upload/b71666998388-20220624.png" width="600" />

## 4. Print the marker
Markers are located at:  
The markers are located under vuforia-sample-android-11-3-4/vuforia-sample-11-3-4/Media after extracting vuforia-sample-android-11-3-4.zip.  
Print target_stones_A4.pdf.

## 5. Run it
Build in Android Studio and run on your phone.  
It'll jump straight to the camera view.  
※I removed the splash screen and the Image Target/Model Target selection screen?they were noisy.  
When you point the camera at the printed marker, the 3D character shown in the "goal image" will appear.  
<img src="https://storage.googleapis.com/zenn-user-upload/7ba378ef9d17-20250906.jpg" width="400" />  
**I did it!!**

# Gotchas
It was tough... I got stuck quite a bit. Leaving notes here in case they help someone.

## 1. Build kept failing
- Initially, I only downloaded the sample code and didn't link the SDK libraries?major headache.
- Also struggled with writing CMakeLists.txt.
Thankfully, Copilot helped me out with solid answers.

## 2. Errors with #include
Was it the difference between #include <> and #include "" that caused the error?
Still not sure.
```diff cpp
- #include <GLESRenderer.h>
+ #include "GLESRenderer.h"
```

## 3. Vuforia feature file (xml, dat) loading error

```diff cpp: AppController.cpp(929,945)
-       imageTargetConfig.databasePath = "StonesAndChips.xml";
+       imageTargetConfig.databasePath = "ImageTargets/StonesAndChips.xml";
```

```diff cpp: GLESRenderer.cpp(54,68)
-       if (!readAsset(assetManager, "Astronaut.obj", data))
+       if (!readAsset(assetManager, "ImageTargets/Astronaut.obj", data))
```

I copied the files under app/src/main/assets, but placing them directly under ImageTargets caused errors.
Changing the path fixed it.  
※This line is crucial when using custom markers, but it's buried in a hard-to-notice spot.  
※Putting files under assets means they can't be downloaded or changed dynamically. Maybe that's intentional?  

↓ Errors occurred in these project-specific changes:
```
app/
└── src/
    └── main/
        └── assets/
            ├── ImageTargets/
            │   ├── Astronaut.jpg
            │   ├── Astronaut.mtl
            │   ├── Astronaut.obj
            │   ├── StonesAndChips.dat
            │   └── StonesAndChips.xml
            └── ModelTargets/
                ├── VikingLander.jpg
                ├── VikingLander.mtl
                ├── VikingLander.obj
                ├── VuforiaMars_ModelTarget.dat
                └── VuforiaMars_ModelTarget.xml
```

## 4. Texture file wouldn't load...
Texture loading via Texture.loadTextureFromApk() seems **deprecated**.  
Fixing it was a pain. Apparently, it has to be loaded into direct memory.  
↓ **Deprecated code**
```diff cpp: VuforiaActivity.cpp(339-340)
-       val astronautTexture = Texture.loadTextureFromApk("Astronaut.jpg", assets)
-       val landerTexture = Texture.loadTextureFromApk("VikingLander.jpg", assets)
```

↓ Fixed code
```diff cpp: MainActivity.cpp(75-81)
+ val astronautbitmap = loadBitmapFromAssets(this@MainActivity, "ImageTargets/Astronaut.jpg")
+ val astronautTexture: ByteBuffer? = astronautbitmap?.let { bitmap ->
+                                         ByteBuffer.allocateDirect(bitmap.byteCount).apply {
+                                             bitmap.copyPixelsToBuffer(this)
+                                             rewind()
+                                         }
+                                     }
```

First load as a bitmap, then push into a ByteBuffer.
You have to use allocateDirect().   
※allocate() won't work since it's not direct memory.

That's it.  
This was the procedure for running an AR sample with Vuforia.

Not the cleanest source code, I'll admit.
