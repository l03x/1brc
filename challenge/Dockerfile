# syntax=docker/dockerfile:1
#
# Two runnable targets:
#   native (default) - GraalVM native-image binary: no JVM, no JIT warmup, ~ms startup
#   jvm              - jlink'd minimal JRE + JDK 25 AOT cache (JEP 483/514/515):
#                      keeps C2 peak performance, cuts class loading/linking at startup
#
# Both expect measurements.txt in the working directory (/data, bind-mounted by compose).

ARG GRAAL_IMAGE=ghcr.io/graalvm/native-image-community:25
ARG JDK_IMAGE=eclipse-temurin:25-jdk

# ---------------------------------------------------------------- jvm
FROM ${JDK_IMAGE} AS jvm-build
WORKDIR /build
COPY src/ src/
RUN javac -d classes src/*.java \
 && jar --create --file /app.jar --main-class Main -C classes . \
 && jlink --add-modules java.base \
          --strip-debug --no-man-pages --no-header-files \
          --output /jre

# Training run on a small synthetic file to record the AOT cache
# (loaded/linked classes + method profiles). Flags must match the runtime ones.
WORKDIR /train
RUN awk 'BEGIN { for (i = 0; i < 200000; i++) printf "Station%d;%.1f\n", i % 413, ((i * 7919) % 1999 - 999) / 10 }' > measurements.txt \
 && /jre/bin/java -XX:+UseSerialGC -XX:-UsePerfData \
        -XX:AOTCacheOutput=/app.aot -jar /app.jar > /dev/null

FROM debian:bookworm-slim AS jvm
# without a UTF-8 locale the JVM encodes stdout as ASCII and station names lose their accents
ENV LANG=C.UTF-8
COPY --from=jvm-build /jre /opt/jre
COPY --from=jvm-build /app.jar /app.aot /app/
WORKDIR /data
ENTRYPOINT ["/opt/jre/bin/java", "-XX:+UseSerialGC", "-XX:-UsePerfData", \
            "-XX:AOTCache=/app/app.aot", "-jar", "/app/app.jar"]

# ------------------------------------------------------------- native
FROM ${GRAAL_IMAGE} AS native-build
# "native" tunes for the build machine's CPU; use x86-64-v3 / compatibility for a portable binary
ARG MARCH=native
WORKDIR /build
COPY src/ src/
RUN javac -d classes src/*.java \
 && native-image -cp classes Main -o 1brc \
        -O3 -march=${MARCH} --no-fallback \
        -H:+UnlockExperimentalVMOptions -H:+StaticExecutableWithDynamicLibC

FROM gcr.io/distroless/base-debian12 AS native
COPY --from=native-build /build/1brc /app/1brc
WORKDIR /data
ENTRYPOINT ["/app/1brc"]
