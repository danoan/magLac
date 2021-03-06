FROM danoan/min-env:2.lcov

WORKDIR /magLac
ADD . /magLac

RUN chmod u+x /magLac/.travis/*
RUN mkdir /magLac/build-release && mkdir /magLac/install

RUN /magLac/.travis/build-magLac.sh \
/magLac \
/magLac/build-release \
/magLac/install \
Release \
OFF

RUN /magLac/.travis/build-magLac.sh \
/magLac \
/magLac/build-debug \
/magLac/install-debug \
Debug \
ON

#The script must run here, otherwise gcda files are not produced
RUN /magLac/.travis/generate-coverage.sh

