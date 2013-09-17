class FSbjsController < ApplicationController
  before_filter :check_auth, :except => :index


  # GET /f_sbjs
  # GET /f_sbjs.xml
  def index
    @f_sbjs = FSbj.all

    respond_to do |format|
      format.html # index.html.erb
      format.xml  { render :xml => @f_sbjs }
    end
  end

  # GET /f_sbjs/1
  # GET /f_sbjs/1.xml
  def show
    @f_sbj = FSbj.find(params[:id])

    respond_to do |format|
      format.html # show.html.erb
      format.xml  { render :xml => @f_sbj }
    end
  end

  # GET /f_sbjs/new
  # GET /f_sbjs/new.xml
  def new
    @f_sbj = FSbj.new

    respond_to do |format|
      format.html # new.html.erb
      format.xml  { render :xml => @f_sbj }
    end
  end

  # GET /f_sbjs/1/edit
  def edit
    @f_sbj = FSbj.find(params[:id])
  end

  # POST /f_sbjs
  # POST /f_sbjs.xml
  def create
    @f_sbj = FSbj.new(params[:f_sbj])

    respond_to do |format|
      if @f_sbj.save
        format.html { redirect_to(@f_sbj, :notice => 'F sbj was successfully created.') }
        format.xml  { render :xml => @f_sbj, :status => :created, :location => @f_sbj }
      else
        format.html { render :action => "new" }
        format.xml  { render :xml => @f_sbj.errors, :status => :unprocessable_entity }
      end
    end
  end

  # PUT /f_sbjs/1
  # PUT /f_sbjs/1.xml
  def update
    @f_sbj = FSbj.find(params[:id])

    respond_to do |format|
      if @f_sbj.update_attributes(params[:f_sbj])
        format.html { redirect_to(@f_sbj, :notice => 'F sbj was successfully updated.') }
        format.xml  { head :ok }
      else
        format.html { render :action => "edit" }
        format.xml  { render :xml => @f_sbj.errors, :status => :unprocessable_entity }
      end
    end
  end

  # DELETE /f_sbjs/1
  # DELETE /f_sbjs/1.xml
  def destroy
    @f_sbj = FSbj.find(params[:id])
    @f_sbj.destroy

    respond_to do |format|
      format.html { redirect_to(f_sbjs_url) }
      format.xml  { head :ok }
    end
  end
end
