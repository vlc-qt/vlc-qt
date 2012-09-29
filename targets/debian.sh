BUILD_DEPS=`awk 'BEGIN {cnt = 1;} /^Build-Depends:/ {split($0, line, ":");split(line[2], deps, ",");for (i in deps) {d = deps[i];sub(/^ */, "", d);sub(/ *$/, "", d);split(d, tokens, " ");packages[cnt] = tokens[1];cnt++;}} END {out = ""; for(i = 1; i <= cnt; i++) {out = out packages[i] " ";} print out; }' debian/control`
CHANGELOG=debian/changelog
NOW=`date -R`
VER=`git describe | sed "s/\([0-9]*\)\.\([0-9]*\)-\([0-9]*\)-.*/\1.\2.\3/"`

build() 
{
    echo >${CHANGELOG} "libvlc-qt (${VER}) unstable; urgency=low"
    echo >>${CHANGELOG}
    echo >>${CHANGELOG} "  * The full changelog can be found in NEWS"
    echo >>${CHANGELOG} "    or by running 'git log' when using Git"
    echo >>${CHANGELOG}
    echo >>${CHANGELOG} " -- Tadej Novak <tadej@tano.si>  ${NOW}"
    
    dpkg-buildpackage -b -us -uc -d

    for a in ../libvlc-qt*${VER}*.deb; do
	versioned_artifact "$a" deb application/x-deb `basename $a`
    done

    for a in ../libvlc-qt*${VER}*.changes; do
	versioned_artifact "$a" changes text/plain `basename $a`
    done
}

clean() 
{
    for a in ../libvlc-qt*${VER}*.deb; do
	rm -f "$a"
    done

    for a in ../libvlc-qt*${VER}*.changes; do
	rm -f "$a"
    done

    dh_clean
}

deps() 
{
    if [[ $EUID -ne 0 ]]; then
	echo "Build dependencies must be installed as root"
	exit 1
    fi
    apt-get -y install ${BUILD_DEPS}
}

buildenv() 
{
    echo $BUILD_DEPS | shasum | awk '{print $1}'
}

eval build
