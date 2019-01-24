package com.github.doraig;


import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;

public class LiftAndShift {

    public static final String SEPERATOR_1 = "\\";

    public static final String SEPERATOR_2 = "/";

    static void copyRecursive(Path source, Path target) throws IOException {
        Files.newDirectoryStream(source).forEach(x -> {
            int index = getIndex(x);
            copyResources(new File(target.toString() + x.toString().substring(index)).toPath(), x);
        });
    }

    private static int getIndex(Path x) {
        String path =  x.toString();
        String indexVal = SEPERATOR_1;
        int index = path.lastIndexOf(indexVal);
        if (index == -1) {
            indexVal = SEPERATOR_2;
            index = path.lastIndexOf(indexVal);
        }
        //if last element
        if (path.length()-1 == index) {
            index = path.substring(0,index).lastIndexOf(indexVal);
        }
        return index;
    }

    private static void copyResources(Path target, Path x) {
        try {
            if (x.endsWith("locales") || x.endsWith("swiftshader")) {
                if (!target.toFile().exists()) {
                    Files.copy(x, target,
                            StandardCopyOption.REPLACE_EXISTING);
                }
                Files.newDirectoryStream(x).forEach(x1 -> {
                    copyResources(new File(target.toString() + x1.toString().substring(getIndex(x1))).toPath(), x1);
                });
            } else {
                Files.copy(getResourceAsStream(x), target,
                        StandardCopyOption.REPLACE_EXISTING);
            }

        } catch (IOException e) {
            throw new RuntimeException("Copy of resources for jcef failed.", e);
        }
    }

    private static InputStream getResourceAsStream(Path x) throws FileNotFoundException {
        InputStream inputStream = LiftAndShift.class.getClassLoader().getResourceAsStream(x.toString().
                substring(isSeperatorExists(x) ? 1 : 0));
        if (inputStream == null) {
            inputStream = new FileInputStream(x.toFile());
        }
        return inputStream;
    }

    private static boolean isSeperatorExists(Path x) {
        return x.toString().startsWith(SEPERATOR_1) || x.toString().startsWith(SEPERATOR_2);
    }


}

