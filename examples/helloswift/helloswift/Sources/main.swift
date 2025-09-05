// Copyright (c) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: MIT

import Nux

class MainWindow: Nux.Window {
    public init () {
        super.init(
            title: "¯\\_(ツ)_/¯",
            width: 800,
            height: 600,
            mode: WindowMode.Standard
        )
        self.rootLayout.kind = Nux.LayoutKind.Fixed

        self.groupBox = self.rootLayout.addWidget<Nux.GroupBox>()
        self.groupBox!.contentLayout.kind = Nux.LayoutKind.Fixed
        self.groupBox!.title = "Vector Graphics"
        self.groupBox!.width = 100 + self.groupBox!.horizontalOverhead
        self.groupBox!.height = 100 + self.groupBox!.verticalOverhead

        self.graphicsBox = self.groupBox!.addWidget<Nux.GraphicsBox>()

        self.rectangle = Nux.VectorPath.buildRectangle(x: 10, y: 10, width: 80, height: 80, radius: 10)
        self.gradientStops1 = [
            GradientStop(position: 0, color: Nux.GVector4D(x: 1, y: 0, z: 0, w: 1)),
            GradientStop(position: 0.5, color: Nux.GVector4D(x: 0, y: 1, z: 0, w: 1)),
            GradientStop(position: 1, color: Nux.GVector4D(x: 0, y: 0, z: 1, w: 1))
        ]
        self.linearGradientPaint = Nux.Paint.buildLinearGradient(
            start: Nux.GVector2D(x: 0, y: 0),
            end: Nux.GVector2D(x: 100, y: 100),
            stops: gradientStops1!
        )

        self.circle = Nux.VectorPath.buildCircle(centerX: 50, centerY: 50, radius: 25)
        self.gradientStops2 = [
            GradientStop(position: 0, color: Nux.GVector4D(x: 1, y: 1, z: 1, w: 1)),
            GradientStop(position: 1, color: Nux.GVector4D(x: 1, y: 1, z: 1, w: 0))
        ]
        self.radialGradientPaint = Nux.Paint.buildRadialGradient(
            center: Nux.GVector2D(x: 50, y: 50),
            radius: 25,
            stops: gradientStops2!
        )

        self.graphicsBox!.renderEventHandler = {
            self.graphicsBox!.clear(
                red: self.clearColor!.x,
                green: self.clearColor!.y,
                blue: self.clearColor!.z,
                alpha: self.clearColor!.w
            )
            self.graphicsBox!.fillPath(path: self.rectangle!, fillPaint: self.linearGradientPaint!);
            self.graphicsBox!.fillPath(path: self.circle!, fillPaint: self.radialGradientPaint!);
        }

        self.helloLabel = self.rootLayout.addWidget<Nux.Label>()
        self.helloLabel!.text = "Made in Swift"

        self.enableToggleButton = self.rootLayout.addWidget<Nux.CheckBox>()
        self.enableToggleButton!.text = "Enable Toggle button"
        self.enableToggleButton!.toggleEventHandler = {
            self.toggleButton!.isEnabled = self.enableToggleButton!.isChecked
        }

        self.toggleButton = self.rootLayout.addWidget<Nux.PushButton>()
        self.toggleButton!.text = "Toggle"
        self.toggleButton!.triggerEventHandler = {
            if self.option1!.isChecked {
                self.option2!.isChecked = true
            } else {
                self.option1!.isChecked = true
            }
        }

        self.group1 = CheckGroup()

        self.option1 = self.rootLayout.addWidget<Nux.RadioButton>(
            group: self.group1!
        )
        self.option1!.text = "Yellow Background"
        self.option1!.toggleEventHandler = {
            self.clearColor = Nux.GVector4D(x: 1, y: 1, z: 0, w: 1)
        }

        self.option2 = self.rootLayout.addWidget<Nux.RadioButton>(
            group: self.group1!
        )
        self.option2!.text = "Orange Background"
        self.option2!.toggleEventHandler = {
            self.clearColor = Nux.GVector4D(x: 1, y: 0.65, z: 0, w: 1)
        }

        self.enableToggleButton!.isChecked = true
        self.option1!.isChecked = true

        var x = 10
        var y = 0
        var maxWidth = 0
        var maxHeight = 0

        y += 10
        self.groupBox!.x = x
        self.groupBox!.y = y
        y += self.groupBox!.height
        maxWidth = max(maxWidth, self.groupBox!.x + self.groupBox!.width)
        maxHeight = max(maxHeight, self.groupBox!.y + self.groupBox!.height)

        self.graphicsBox!.x = 0
        self.graphicsBox!.y = 0
        self.graphicsBox!.width = 100
        self.graphicsBox!.height = 100

        y += 10
        self.helloLabel!.x = x
        self.helloLabel!.y = y
        y += self.helloLabel!.height
        maxWidth = max(maxWidth, self.helloLabel!.x + self.helloLabel!.width)
        maxHeight = max(maxHeight, self.helloLabel!.y + self.helloLabel!.height)

        x = self.groupBox!.x + self.groupBox!.width + 10;
        y = 0;

        y += 10
        self.enableToggleButton!.x = x
        self.enableToggleButton!.y = y
        y += self.enableToggleButton!.height
        maxWidth = max(maxWidth, self.enableToggleButton!.x + self.enableToggleButton!.width)
        maxHeight = max(maxHeight, self.enableToggleButton!.y + self.enableToggleButton!.height)

        y += 10
        self.toggleButton!.x = x
        self.toggleButton!.y = y
        y += self.toggleButton!.height
        maxWidth = max(maxWidth, self.toggleButton!.x + self.toggleButton!.width)
        maxHeight = max(maxHeight, self.toggleButton!.y + self.toggleButton!.height)

        y += 10
        self.option1!.x = x
        self.option1!.y = y
        y += self.option1!.height
        maxWidth = max(maxWidth, self.option1!.x + self.option1!.width)
        maxHeight = max(maxHeight, self.option1!.y + self.option1!.height)

        y += 10
        self.option2!.x = x
        self.option2!.y = y
        y += self.option1!.height
        maxWidth = max(maxWidth, self.option2!.x + self.option2!.width)
        maxHeight = max(maxHeight, self.option2!.y + self.option2!.height)

        self.width = maxWidth + 10
        self.height = maxHeight + 10

        self.center()
        self.rootLayout.show()
    }

    public override func handleCloseEvent (
        closeEvent: CloseEvent
    ) {
        if title != "Confirm" {
            title = "Confirm"
            closeEvent.shouldClose = false
        }
    }

    private var groupBox: Nux.GroupBox? = nil
    private var graphicsBox: Nux.GraphicsBox? = nil
    private var rectangle: Nux.VectorPath? = nil
    private var gradientStops1: [Nux.GradientStop]? = nil
    private var linearGradientPaint: Nux.Paint? = nil
    private var circle: Nux.VectorPath? = nil
    private var gradientStops2: [Nux.GradientStop]? = nil
    private var radialGradientPaint: Nux.Paint? = nil
    private var helloLabel: Nux.Label? = nil
    private var enableToggleButton: Nux.CheckBox? = nil
    private var toggleButton: Nux.PushButton? = nil
    private var group1: Nux.CheckGroup? = nil
    private var option1: Nux.RadioButton? = nil
    private var option2: Nux.RadioButton? = nil
    private var clearColor: Nux.GVector4D? = nil
}

@main
struct HelloSwift {
    static func main () -> Void {
        let app = Nux.Application(args: CommandLine.arguments)
        print(Nux.Application.encoding)

        let mainWindow = MainWindow()
        mainWindow.show()

        app.run()
    }
}
