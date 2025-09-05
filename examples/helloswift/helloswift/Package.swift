// swift-tools-version: 5.9
import PackageDescription

let package = Package(
    name: "HelloSwift",
    products: [
        .executable(name: "HelloSwift", targets: ["HelloSwift"]),
    ],
    dependencies: [
        .package(path: "../../../bindings/swift/Nux"),
    ],
    targets: [
        .executableTarget(
            name: "HelloSwift",
            dependencies: [
                .product(name: "Nux", package: "Nux")
            ],
            path: ".",
            cSettings: [
                .headerSearchPath("vendor/include"),
                .define("NUXC_STRING_TYPE_STD_U8STRING")
            ],
            linkerSettings: [
                .unsafeFlags([
                    "-Lvendor", "-lnux8c",
                    "-Xlinker", "-rpath", "-Xlinker", "./vendor"
                ])
            ]
        ),
    ]
)
