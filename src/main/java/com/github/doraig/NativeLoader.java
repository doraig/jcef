package com.github.doraig;

import java.io.File;
import java.io.IOException;
import java.lang.reflect.Field;
import java.net.URISyntaxException;
import java.net.URL;
import java.nio.file.*;
import java.util.Arrays;
import java.util.logging.Level;
import java.util.logging.Logger;

public class NativeLoader {

    private static final Logger LOG = Logger.getLogger(NativeLoader.class.getName());
    private static final String JAR = "jar";
    private static final String JAVA_IO_TMPDIR = "java.io.tmpdir";
    private static final String JCEF = "org.github.doraig.jcef.";
    private static final String PATH_LIB = "lib";
    private static final String USR_PATHS = "usr_paths";

    public NativeLoader() {
    }

    public static void loadLibrary() {
        try {
            addLibraryDir(saveLibrary());
            Runtime.getRuntime().addShutdownHook(new Thread(() -> {

                try {
                    if (System.getProperty("os.name").startsWith("win")) {
                        Runtime.getRuntime().exec("TASKKILL /F /IM jcef_helper.exe");
                    }
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }));
        } catch (Exception e) {
            LOG.log(Level.ALL, "Could not load library from resource, trying fallback lookup through System.loadLibrary");
        }
    }

    private static void addLibraryDir(String libraryPath) throws Exception {
        Field userPathsField = ClassLoader.class.getDeclaredField(USR_PATHS);
        userPathsField.setAccessible(true);
        String[] paths = ((String[]) userPathsField.get(null));
        StringBuilder sb = new StringBuilder();
        Arrays.stream(paths).filter(x -> !libraryPath.equals(x)).forEach(x -> sb.append(x).append(File.pathSeparatorChar));
        sb.append(libraryPath);
        System.setProperty("java.library.path", sb.toString());
        Field sysPathsField = ClassLoader.class.getDeclaredField("sys_paths");
        sysPathsField.setAccessible(true);
        sysPathsField.set(null, null);
    }

    private static String saveLibrary() throws IOException, URISyntaxException {

        String srcLib = PATH_LIB;
        URL resource = NativeLoader.class.getClassLoader().getResource(srcLib);
        File tmpDir = new File(System.getProperty(JAVA_IO_TMPDIR) + JCEF
                + System.getProperty("os.arch"));
        if (!tmpDir.exists()) {
            tmpDir.mkdir();
        }
        if (resource.getPath().contains(JAR)) {
            try {
                URL jar = NativeLoader.class.getProtectionDomain().getCodeSource().getLocation();
                Path jarFile = Paths.get(jar.toURI());
                FileSystem fs = FileSystems.newFileSystem(jarFile, null);
                LiftAndShift.copyRecursive(fs.getPath(srcLib), tmpDir.toPath());

            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        } else {
            LiftAndShift.copyRecursive(Paths.get(resource.toURI()), tmpDir.toPath());
        }

        return tmpDir.getAbsolutePath();
    }
}
